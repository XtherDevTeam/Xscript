//
// Created by Jerry Chou on 2022/5/13.
//

#include "EnvironmentStack.hpp"

namespace XScript {
    EnvironmentStack::EnvironmentStack() = default;

    EnvironmentStackItem EnvironmentStack::PopValueFromStack() {
        auto R = Elements.back();
        Elements.pop_back();
        return R;
    }

    void EnvironmentStack::PushValueToStack(EnvironmentStackItem Item) {
        Elements.push_back(Item);
    }
} // XScript