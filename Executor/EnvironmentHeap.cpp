//
// Created by Jerry Chou on 2022/5/14.
//

#include "EnvironmentHeap.hpp"

namespace XScript {
    EnvironmentHeap::EnvironmentHeap() {
    }

    XHeapIndexType EnvironmentHeap::PushElement(EnvObject Object) {
        CreatedUnfreeElement++;
        if (!UsedIndexes.empty()) {
            auto Idx = *UsedIndexes.begin();
            UsedIndexes.erase(UsedIndexes.begin());
            HeapData[Idx] = Object;
            return Idx;
        }
        HeapData[AllocatedElementCount] = Object;
        return AllocatedElementCount++;
    }

    EnvironmentHeap::~EnvironmentHeap() {
        std::set<void *> DoubleFreeFucker;
        for (auto &I : HeapData) {
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
                    break;
                }
                default: {
                    I.second.DestroyObject();
                    I.second = {};
                    break;
                }
            }
        }
        HeapData.clear();
    }

} // XScript