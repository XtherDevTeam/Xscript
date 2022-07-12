//
// Created by Jerry Chou on 2022/5/13.
//

#include "EnvironmentStackFramesInfomation.hpp"

namespace XScript {
    EnvironmentStackFramesInformation::EnvironmentStackFramesInformation(
            EnvironmentStackFramesInformation::FrameKind kind, XIndexType from, XIndexType length,
            ProgramCounterInformation returnAddress) : Kind(kind),
                                                       From(from),
                                                       Length(length), ReturnAddress(returnAddress) {

    }
} // XScript