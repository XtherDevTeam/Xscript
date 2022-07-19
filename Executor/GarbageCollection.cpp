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
        std::queue<XHeapIndexType> Queue;
        for (auto &I: Env.Stack.Elements) {
            if (I.Kind == EnvironmentStackItem::ItemKind::HeapPointer)
                Queue.push(I.Value.HeapPointerVal);
        }
        while (!Queue.empty()) {
            auto &Element = Env.Heap.HeapData[Queue.back()];
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

        for (auto &I: Env.Heap.HeapData) {
            if (!I.Marked) {
                I.DestroyObject();
                I = {};
            }
        }
    }

    [[noreturn]] void GarbageCollection::GCThreadFunc(GarbageCollection &This) {
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(10));
            This.Start();
        }
    }

    void GarbageCollection::Init() {
        GCThread = std::thread(GCThreadFunc, std::ref(*this));
        GCThread.detach();
    }
} // XScript