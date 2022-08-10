//
// Created by chou on 22-7-19.
//

#include <queue>
#include <unordered_set>
#include "GarbageCollection.hpp"

#include "../Share/Xqueue.hpp"

namespace XScript {

    GarbageCollection::GarbageCollection(Environment &Env) : Env(Env) {
        ThreadFlag = true;
        ActiveGCThread = (std::thread){ActiveGCThreadFunc, std::ref(*this)};
    }

    /**
     * BFS
     */
    void GarbageCollection::Start(bool force) {
        if (force || ActiveCheck()) {
            XScript2::xqueue<XHeapIndexType> Queue;
            for (auto &I: Env.Packages) {
                for (auto &J: I.second.Statics) {
                    if (J.Kind == EnvironmentStackItem::ItemKind::HeapPointer)
                        Queue.push(J.Value.HeapPointerVal);
                }
            }
            for (XIndexType TID = 0; TID < MaxThreadCount; TID++) {
                for (auto &I: Env.Threads[TID].Stack.Elements) {
                    if (I.Kind == EnvironmentStackItem::ItemKind::HeapPointer)
                        Queue.push(I.Value.HeapPointerVal);
                }
            }
            // 标记
            XHeapIndexType Top = 0;
            XHeapIndexType AAllocCount = 0;
            while (!Queue.empty()) {
                Top = std::max(Top, Queue.front());

                auto &Element = Env.Heap.HeapData[Queue.front()];
                Queue.pop();
                if (Element.Marked)
                    continue;
                Element.Marked = true;
                switch (Element.Kind) {
                    case EnvObject::ObjectKind::ClassObject:
                        for (auto &I: Element.Value.ClassObjectPointer->Members) {
                            Queue.push(I.second);
                        }
                        break;
                    case EnvObject::ObjectKind::ArrayObject:
                        for (auto &I: Element.Value.ArrayObjectPointer->Elements) {
                            Queue.push(I);
                        }
                        break;
                    default:
                        break;
                }
                AAllocCount++;
            }

            // 清除
            std::set<void *> FreeAddresses;
            for (XIndexType I = Env.Heap.AllocatedElementCount - 1; I + 1; I--) {
                if (Env.Heap.HeapData[I].Marked) {
                    Env.Heap.HeapData[I].Marked = false;
                    continue;
                } else {
                    switch (Env.Heap.HeapData[I].Kind) {
                        case EnvObject::ObjectKind::BytesObject:
                        case EnvObject::ObjectKind::StringObject:
                        case EnvObject::ObjectKind::ClassObject:
                        case EnvObject::ObjectKind::ArrayObject: {
                            if (FreeAddresses.count(static_cast<void *>(Env.Heap.HeapData[I].Value.ClassObjectPointer))) {
                                CreatedUnfreeElement--;
                                Env.Heap.HeapData[I] = {};
                                Env.Heap.UsedElementSet.insert(I);
                                continue;
                            } else {
                                FreeAddresses.insert(static_cast<void *>(Env.Heap.HeapData[I].Value.ClassObjectPointer));
                            }
                        }
                        default:
                            break;
                    }
                    Env.Heap.HeapData[I].DestroyObject();
                    Env.Heap.HeapData[I] = {};
                    Env.Heap.UsedElementSet.insert(I);
                }
            }

            Limit = Env.Heap.AllocatedElementCount > AAllocCount ? Env.Heap.AllocatedElementCount : Env.Heap.AllocatedElementCount + EnvHeapGCStartCondition;
        }
    }

    bool GarbageCollection::PassiveCheck() const {
        return Env.Heap.UsedElementSet.empty() &&
               Env.Heap.AllocatedElementCount >= EnvHeapDataAllocateSize - EnvHeapGCStartCondition;
    }

    bool GarbageCollection::ActiveCheck() const {
        return Env.Heap.UsedElementSet.empty() && Env.Heap.AllocatedElementCount >= Limit;
    }

    [[noreturn]] void GarbageCollection::ActiveGCThreadFunc(GarbageCollection &GC) {
        while (GC.ThreadFlag) {
            if (GC.ActiveCheck()) {
                InterpreterLock.lock();
                GC.Start(true);
                InterpreterLock.unlock();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
        }
    }

    void GarbageCollection::Stop() {
        ThreadFlag = false;
        if (ActiveGCThread.joinable())
            ActiveGCThread.join();
    }
} // XScript