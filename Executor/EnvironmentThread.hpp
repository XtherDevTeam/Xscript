//
// Created by chou on 22-7-30.
//

#ifndef XSCRIPT2_ENVIRONMENTTHREAD_HPP
#define XSCRIPT2_ENVIRONMENTTHREAD_HPP

#include "ProgramCounterInformation.hpp"
#include "EnvironmentStack.hpp"

namespace XScript {

    class EnvironmentThread {
    public:
        bool IsBusy;
        EnvironmentStack Stack;
        ProgramCounterInformation PC;

        EnvironmentThread();
    };

} // XScript

#endif //XSCRIPT2_ENVIRONMENTTHREAD_HPP
