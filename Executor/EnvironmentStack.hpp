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
        EnvironmentStack(EnvironmentStackFramesInformation &FrameInfo);

        XArray<EnvironmentStackItem> Elements;
        XArray<EnvironmentStackFramesInformation> FramesInformation;

        EnvironmentStack();

        void PushValueToStack(EnvironmentStackItem Item);

        EnvironmentStackItem PopValueFromStack();

        EnvironmentStackItem GetValueFromStack(XIndexType IndexInFrame);

        void StoreValueToIndex(XIndexType IndexInFrame, EnvironmentStackItem Item);
    };

} // XScript

#endif //XSCRIPT2_ENVIRONMENTSTACK_HPP
