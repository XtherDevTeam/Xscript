//
// Created by Jerry Chou on 2022/5/13.
//

#include "EnvironmentStack.hpp"

namespace XScript {
    EnvironmentStack::EnvironmentStack(EnvironmentStackFramesInformation &FrameInfo) {
        FramesInformation.push_back(FrameInfo);
    }

    EnvironmentStack::EnvironmentStack() = default;
} // XScript