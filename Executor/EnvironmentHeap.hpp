//
// Created by Jerry Chou on 2022/5/14.
//

#ifndef XSCRIPT2_ENVIRONMENTHEAP_HPP
#define XSCRIPT2_ENVIRONMENTHEAP_HPP

#include <stack>
#include <set>
#include "../Share/Utils.hpp"
#include "EnvObject.hpp"

namespace XScript {
    /**
     * Allocate 1024 elements when heap is created.
     */
    constexpr XIndexType EnvHeapDataAllocateSize = 1048576;

    class EnvironmentHeap {
    public:
        XIndexType AllocatedElementCount{};
        XArray<EnvObject> HeapData;
        std::set<XHeapIndexType> UsedElementSet;

        EnvironmentHeap();

        XHeapIndexType PushElement(EnvObject Object);

        void PopElement(XHeapIndexType Object);
    };

} // XScript

#endif //XSCRIPT2_ENVIRONMENTHEAP_HPP
