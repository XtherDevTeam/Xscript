//
// Created by Jerry Chou on 2022/5/13.
//

#include "EnvironmentStack.hpp"

namespace XScript {
    EnvironmentStack::EnvironmentStack(EnvironmentStackFramesInformation &FrameInfo) {
        FramesInformation.push_back(FrameInfo);
    }

    EnvironmentStackItem EnvironmentStack::PopValueFromStack() {
        auto R = Elements[Elements.size() - 1];
        Elements.pop_back();
        FramesInformation.back().Length--;
        return R;
    }

    void EnvironmentStack::PushValueToStack(EnvironmentStackItem Item) {
        Elements.push_back(Item);
        FramesInformation.back().Length++;
    }

    EnvironmentStackItem EnvironmentStack::GetValueFromStack(XIndexType IndexInFrame) {
        XIndexType RealPos = FramesInformation[FramesInformation.size() - 1].From + IndexInFrame;
        try {
            return Elements.at(RealPos);
        } catch (std::exception &E) {
            throw;
        }
    }

    void EnvironmentStack::StoreValueToIndex(XIndexType IndexInFrame, EnvironmentStackItem Item) {
        XIndexType RealPos = FramesInformation[FramesInformation.size() - 1].From + IndexInFrame;
        Elements[RealPos] = Item;
    }

    EnvironmentStack::EnvironmentStack() = default;
} // XScript