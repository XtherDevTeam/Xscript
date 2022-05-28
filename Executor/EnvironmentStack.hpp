//
// Created by Jerry Chou on 2022/5/13.
//

#ifndef XSCRIPT2_ENVIRONMENTSTACK_HPP
#define XSCRIPT2_ENVIRONMENTSTACK_HPP

#include "../Share/Utils.hpp"
#include "EnvironmentStackItem.hpp"
#include "EnvironmentStackFramesInfomation.hpp"

namespace XScript {

    /**
     * Environment Stack of XScript Bytecode Interpreter
     *
     * @warning
     * You MUST create a initial frame manually before you use it.
     */
    class EnvironmentStack {
    public:
        explicit EnvironmentStack(EnvironmentStackFramesInformation &FrameInfo);

        XArray<EnvironmentStackItem> Elements;
        XArray<EnvironmentStackFramesInformation> FramesInformation;

        EnvironmentStack();

        inline void PushValueToStack(EnvironmentStackItem Item) {
            Elements.push_back(Item);
            FramesInformation.back().Length++;
        }

        inline EnvironmentStackItem PopValueFromStack() {
            auto R = Elements[Elements.size() - 1];
            Elements.pop_back();
            FramesInformation.back().Length--;
            return R;
        }

        inline EnvironmentStackItem GetValueFromStack(XIndexType IndexInFrame) {
            XIndexType RealPos = FramesInformation[FramesInformation.size() - 1].From + IndexInFrame;
            try {
                return Elements.at(RealPos);
            } catch (std::exception &E) {
                throw;
            }
        }

        inline void StoreValueToIndex(XIndexType IndexInFrame, EnvironmentStackItem Item) {
            XIndexType RealPos = FramesInformation[FramesInformation.size() - 1].From + IndexInFrame;
            Elements[RealPos] = Item;
        }

    };

} // XScript

#endif //XSCRIPT2_ENVIRONMENTSTACK_HPP
