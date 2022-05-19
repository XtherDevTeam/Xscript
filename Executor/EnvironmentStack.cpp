//
// Created by Jerry Chou on 2022/5/13.
//

#include "EnvironmentStack.hpp"

namespace XScript {
    EnvironmentStack::EnvironmentStack(EnvironmentStackFramesInformation& FrameInfo) {
        FramesInformation.push_back(FrameInfo);
    }

    EnvironmentStackItem EnvironmentStack::PopValueFromStack() {
        auto R = Elements.back();
        Elements.pop_back();
        return R;
    }

    void EnvironmentStack::PushValueToStack(EnvironmentStackItem Item) {
        Elements.push_back(Item);
    }

    EnvironmentStackItem EnvironmentStack::GetValueFromStack(XIndexType IndexInFrame) {
        XIndexType RealPos = FramesInformation.back().From + IndexInFrame;
        try {
            return Elements.at(RealPos);
        } catch (std::exception &E) {
            throw ;
        }
    }

    EnvironmentStack::EnvironmentStack() = default;
} // XScript