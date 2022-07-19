//
// Created by chou on 22-7-19.
//

#include <queue>
#include "GarbageCollection.hpp"

namespace XScript {

    GarbageCollection::GarbageCollection(Environment &Env) : Env(Env) {

    }

    /**
     * BFS
     */
    void GarbageCollection::Start() {
        if (Check()) {
            std::queue<XHeapIndexType> Queue;
            for (auto &I: Env.Packages) {
                for (auto &J: I.second.Statics) {
                    if (J.Kind == EnvironmentStackItem::ItemKind::HeapPointer)
                        Queue.push(J.Value.HeapPointerVal);
                }
            }
            for (auto &I: Env.Stack.Elements) {
                if (I.Kind == EnvironmentStackItem::ItemKind::HeapPointer)
                    Queue.push(I.Value.HeapPointerVal);
            }
            // 标记
            while (!Queue.empty()) {
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
            }

            // 清除
            for (XIndexType index = 0; index < Env.Heap.AllocatedElementCount; index++) {
                auto &I = Env.Heap.HeapData[index];
                if (!I.Marked) {
                    I.DestroyObject();
                    Env.Heap.UsedElementSet.insert(index);
                }
            }

            // 执行完GC之后 查看堆尾部是否有未使用的元素，将其回收
            for (XIndexType index = Env.Heap.AllocatedElementCount - 1; index != 0; index--) {
                if (!Env.Heap.HeapData[index].Marked) {
                    --Env.Heap.AllocatedElementCount;
                }
            }
            Limit = Env.Heap.AllocatedElementCount + EnvHeapGCStartCondition;
        }
    }

    bool GarbageCollection::Check() const {
        return Env.Heap.AllocatedElementCount > Limit;
    }
} // XScript