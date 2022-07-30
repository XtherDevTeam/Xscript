//
// Created by chou on 22-7-30.
//

#include "EnvironmentThreadPool.hpp"

namespace XScript {
    EnvironmentThreadPool::EnvironmentThreadPool(){
        Pool = new EnvironmentThread[MaxThreadCount];
        for (XIndexType i = 0;i < MaxThreadCount;i++) {
            Pool[i] = {};
        }
    }

    EnvironmentThread &EnvironmentThreadPool::operator[](XIndexType Idx) const {
        return Pool[Idx];
    }

    XIndexType EnvironmentThreadPool::Allocate() {
        for (int i = 0;i < MaxThreadCount;i++) {
            if(!Pool[i].IsBusy)
                return i;
        }
        return -1;
    }

    EnvironmentThreadPool::~EnvironmentThreadPool() {
        delete[] Pool;
    }
} // XScript