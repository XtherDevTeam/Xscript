//
// Created by Jerry Chou on 2022/5/14.
//

#ifndef XSCRIPT2_ENVIRONMENTHEAP_HPP
#define XSCRIPT2_ENVIRONMENTHEAP_HPP

#include <stack>
#include <set>
#include <mutex>
#include <queue>
#include "../Share/Utils.hpp"
#include "../Share/Xqueue.hpp"
#include "EnvObject.hpp"

namespace XScript {
    class EnvironmentHeap {
    public:
        XIndexType AllocatedElementCount{};
        XMap<XHeapIndexType, EnvObject> HeapData;
        std::unordered_set<XHeapIndexType> UsedIndexes;

        EnvironmentHeap();

        XHeapIndexType PushElement(EnvObject Object);

        ~EnvironmentHeap();
    };

} // XScript

#endif //XSCRIPT2_ENVIRONMENTHEAP_HPP
