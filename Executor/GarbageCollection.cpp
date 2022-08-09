//
// Created by chou on 22-7-19.
//

#include <queue>
#include <unordered_set>
#include "GarbageCollection.hpp"

#include "../Share/Xqueue.hpp"

namespace XScript {

    GarbageCollection::GarbageCollection(Environment &Env) : Env(Env) {
        ActiveGCThread = (std::thread){ActiveGCThreadFunc, std::ref(*this)};
    }

    /**
     * BFS
     */
    void GarbageCollection::Start(bool force) {
        if (force || PassiveCheck()) {
            XScript2::xqueue<XHeapIndexType> Queue;
            for (auto &I: Env.Packages) {
                for (auto &J: I.second.Statics) {
                    if (J.Kind == EnvironmentStackItem::ItemKind::HeapPointer)
                        Queue.push(J.Value.HeapPointerVal);
                }
            }
            for (XIndexType TID = 0; TID < MaxThreadCount; TID++) {
                if (!Env.Threads[TID].IsBusy)
                    continue;
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
            std::unordered_set<void *> FreedAddresses;
            for (XIndexType index = Env.Heap.AllocatedElementCount - 1; index + 1; index--) {
                auto &I = Env.Heap.HeapData[index];
                if (!I.Marked) {
                    if (I.Kind == EnvObject::ObjectKind::ClassObject || I.Kind == EnvObject::ObjectKind::StringObject ||
                        I.Kind == EnvObject::ObjectKind::BytesObject || I.Kind == EnvObject::ObjectKind::ArrayObject) {
                        if (FreedAddresses.count(static_cast<void *>(I.Value.ClassObjectPointer))) {
                            Env.Heap.UsedElementSet.insert(index);
                            I = {};
                            continue;
                        } else {
                            FreedAddresses.insert(static_cast<void *>(I.Value.ClassObjectPointer));
                        }
                    }
                    I.DestroyObject();
                    I = {};
                    Env.Heap.UsedElementSet.insert(index);
                } else {
                    Env.Heap.HeapData[index].Marked = !Env.Heap.HeapData[index].Marked;
                }
            }

            Limit = std::min(AAllocCount + EnvHeapGCStartCondition, EnvHeapDataAllocateSize);
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
        while (true) {
            if (GC.ActiveCheck()) {
                InterpreterLock.lock();
                GC.Start(true);
                InterpreterLock.unlock();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }

    GarbageCollection::~GarbageCollection() {
        if (ActiveGCThread.joinable())
            ActiveGCThread.detach();
    }
} // XScript