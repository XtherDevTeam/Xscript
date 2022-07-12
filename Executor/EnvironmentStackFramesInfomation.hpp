//
// Created by Jerry Chou on 2022/5/13.
//

#ifndef XSCRIPT2_ENVIRONMENTSTACKFRAMESINFOMATION_HPP
#define XSCRIPT2_ENVIRONMENTSTACKFRAMESINFOMATION_HPP

#include "../Share/Utils.hpp"
#include "ProgramCounterInformation.hpp"

namespace XScript {

    /**
     * Saves information for each environment stack frames.
     */
    class EnvironmentStackFramesInformation {
    public:
        enum class FrameKind : XInteger {
            FunctionStackFrame,
            MethodStackFrame,
        } Kind{};

        ProgramCounterInformation ReturnAddress;

        XIndexType From{};

        XIndexType Length{};

        EnvironmentStackFramesInformation(
                EnvironmentStackFramesInformation::FrameKind kind, XIndexType from, XIndexType length,
                ProgramCounterInformation returnAddress);
    };


} // XScript

#endif //XSCRIPT2_ENVIRONMENTSTACKFRAMESINFOMATION_HPP
