//
// Created by chou on 22-7-30.
//

#ifndef XSCRIPT2_ENVIRONMENTTHREADPOOL_HPP
#define XSCRIPT2_ENVIRONMENTTHREADPOOL_HPP

#include "../Share/Config.hpp"
#include "EnvironmentThread.hpp"

namespace XScript {
    class EnvironmentThreadPool {
    public:

        EnvironmentThread* Pool;

        EnvironmentThreadPool();

        XIndexType Allocate();

        EnvironmentThread& operator[](XIndexType Idx) const;

        ~EnvironmentThreadPool();
    };

} // XScript

#endif //XSCRIPT2_ENVIRONMENTTHREADPOOL_HPP
