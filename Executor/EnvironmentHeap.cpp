//
// Created by Jerry Chou on 2022/5/14.
//

#include "EnvironmentHeap.hpp"
#include "../Share/Exceptions/HeapOverflowException.hpp"

namespace XScript {
    EnvironmentHeap::EnvironmentHeap() {
        HeapData = new EnvObject[EnvHeapDataAllocateSize];
    }

    XHeapIndexType EnvironmentHeap::PushElement(EnvObject Object) {
        CreatedUnfreeElement++;
        if (!UsedElementSet.empty()) {
            auto Index = *UsedElementSet.begin();
            UsedElementSet.erase(Index);
            HeapData[Index] = Object;

            return Index;
        } else if (AllocatedElementCount == EnvHeapDataAllocateSize) {
            throw HeapOverflowException(L"heap elements limit exceeded: debug heap elements count: " + std::to_wstring(CreatedUnfreeElement));
        }
        HeapData[AllocatedElementCount] = Object;

        return AllocatedElementCount++;
    }

    EnvironmentHeap::~EnvironmentHeap() {

        std::set<void *> FreedAddresses;
        for (XIndexType index = 0; index < AllocatedElementCount; index++) {
            auto &I = HeapData[index];
            if (!I.Marked) {
                if (I.Kind == EnvObject::ObjectKind::ClassObject || I.Kind == EnvObject::ObjectKind::StringObject || I.Kind == EnvObject::ObjectKind::BytesObject ||
                    I.Kind == EnvObject::ObjectKind::ArrayObject) {
                    if (FreedAddresses.count(static_cast<void *>(I.Value.ClassObjectPointer))) {
                        CreatedUnfreeElement--;
                        UsedElementSet.insert(index);
                        I = {};
                        continue;
                    } else {
                        FreedAddresses.insert(static_cast<void *>(I.Value.ClassObjectPointer));
                    }
                }
                I.DestroyObject();
                I = {};
                UsedElementSet.insert(index);
            } else {
                HeapData[index].Marked = !HeapData[index].Marked;
            }
        }
        UsedElementSet.clear();
        delete[] HeapData;
    }

} // XScript