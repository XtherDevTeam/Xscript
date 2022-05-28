//
// Created by Jerry Chou on 2022/5/14.
//

#include "EnvironmentHeap.hpp"
#include "../Share/Exceptions/HeapOverflowException.hpp"

namespace XScript {
    EnvironmentHeap::EnvironmentHeap() {
        HeapData.resize(EnvHeapDataAllocateSize);
    }

    XHeapIndexType EnvironmentHeap::PushElement(EnvObject Object) {
        if (!UsedElementSet.empty()) {
            auto Index = *UsedElementSet.begin();
            HeapData[Index] = Object;
            return Index;
        } else if (AllocatedElementCount == EnvHeapDataAllocateSize) {
            throw HeapOverflowException(L"heap elements limit exceeded");
        }
        HeapData[AllocatedElementCount] = Object;
        return AllocatedElementCount++;
    }

    void EnvironmentHeap::PopElement(XHeapIndexType Object) {
        switch (HeapData[Object].Kind) {
            case EnvObject::ObjectKind::ClassObject:
                /* TODO: Add classes to XScript2 */
                break;
            case EnvObject::ObjectKind::ArrayObject:
                for (XIndexType Index = 0; Index < HeapData[Object].Value.ArrayObjectPointer->Length(); ++Index) {
                    PopElement(HeapData[Object].Value.ArrayObjectPointer->Elements[Index]);
                }
                break;
            case EnvObject::ObjectKind::StringObject:
            case EnvObject::ObjectKind::Integer:
            case EnvObject::ObjectKind::Decimal:
            case EnvObject::ObjectKind::Boolean:
                break;
        }
        HeapData[Object].DestroyObject();
        if (Object == AllocatedElementCount - 1) {
            AllocatedElementCount--;
        } else {
            UsedElementSet.insert(Object);
        }
    }

} // XScript