//
// Created by Jerry Chou on 2022/5/13.
//

#ifndef XSCRIPT2_ENVIRONMENTSTACK_HPP
#define XSCRIPT2_ENVIRONMENTSTACK_HPP

#include "../Share/Utils.hpp"
#include "EnvironmentStackItem.hpp"
#include "EnvironmentStackFramesInfomation.hpp"

namespace XScript {

    class EnvironmentStack {
    public:
        XArray<EnvironmentStackItem> Elements;
        XArray<EnvironmentStackFramesInformation> FramesInformation;

        EnvironmentStack();

        void PushValueToStack(EnvironmentStackItem Item);

        EnvironmentStackItem PopValueFromStack();
    };

} // XScript

#endif //XSCRIPT2_ENVIRONMENTSTACK_HPP
