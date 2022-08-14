//
// Created by chou on 22-7-19.
//

#include <queue>
#include <set>
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
        if (force || PassiveCheck()) {
            std::queue<XHeapIndexType> Queue;
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

            XHeapIndexType AAllocCount = 0;
            while (!Queue.empty()) {
                AAllocCount++;
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
                    case EnvObject::ObjectKind::ClosurePointer:
                        for (auto &I: Element.Value.ClosurePointer->OuterVars) {
                            Queue.push(I);
                        }
                        break;
                    default:
                        break;
                }
            }

            std::set<void *> DoubleFreeFucker;
            for (auto &I : Env.Heap.HeapData) {
                if (I.second.Marked) {
                    I.second.Marked = !I.second.Marked;
                } else {
                    switch (I.second.Kind) {
                        case EnvObject::ObjectKind::ArrayObject:
                        case EnvObject::ObjectKind::ClassObject:
                        case EnvObject::ObjectKind::StringObject:
                        case EnvObject::ObjectKind::BytesObject: {
                            if (DoubleFreeFucker.count(static_cast<void *>(I.second.Value.ClassObjectPointer))) {
                                I.second = {};
                            } else {
                                DoubleFreeFucker.insert(static_cast<void *>(I.second.Value.ClassObjectPointer));
                                I.second.DestroyObject();
                                I.second = {};
                            }
                            Env.Heap.UsedIndexes.insert(I.first);
                            break;
                        }
                        default: {
                            I.second.DestroyObject();
                            I.second = {};
                            Env.Heap.UsedIndexes.insert(I.first);
                            break;
                        }
                    }
                }
            }
            for (auto &I : Env.Heap.UsedIndexes) {
                Env.Heap.HeapData.erase(I);
            }

            Limit = AAllocCount + EnvHeapGCStartCondition;
        }
    }

    bool GarbageCollection::PassiveCheck() const {
        return (Env.Heap.UsedIndexes.empty() && Env.Heap.HeapData.size() >= EnvHeapDataAllocateSize / 2);
    }

    bool GarbageCollection::ActiveCheck() const {
        return (Env.Heap.UsedIndexes.empty() && Env.Heap.HeapData.size() >= Limit);
    }

    void GarbageCollection::ActiveGCThreadFunc(GarbageCollection &GC) {
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

    GarbageCollection::~GarbageCollection() {
        Stop();
    }
} // XScript