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
     * When there are 256 elements in heap, start gc process.
     */
    constexpr XIndexType EnvHeapGCStartCondition = 256;
    /**
     * Allocate 1024 elements when heap is created.
     */
    constexpr XIndexType EnvHeapDataAllocateSize = 1024;

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
