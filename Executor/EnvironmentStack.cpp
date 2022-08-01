//
// Created by Jerry Chou on 2022/5/13.
//

#include "EnvironmentStack.hpp"

namespace XScript {
    std::mutex StackLock;

    EnvironmentStack::EnvironmentStack(EnvironmentStackFramesInformation &FrameInfo) {
        FramesInformation.push_back(FrameInfo);
    }

    EnvironmentStack::EnvironmentStack() : FramesInformation(), Elements() {}
} // XScript