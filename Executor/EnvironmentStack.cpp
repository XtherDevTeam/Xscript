//
// Created by Jerry Chou on 2022/5/13.
//

#include "EnvironmentStack.hpp"

namespace XScript {
    EnvironmentStack::EnvironmentStack(EnvironmentStackFramesInformation &FrameInfo) {
        FramesInformation.push_back(FrameInfo);
    }

    EnvironmentStackItem EnvironmentStack::PopValueFromStack() {
        auto R = Elements.back();
        Elements.pop_back();
        FramesInformation.back().Length--;
        return R;
    }

    void EnvironmentStack::PushValueToStack(EnvironmentStackItem Item) {
        Elements.push_back(Item);
        FramesInformation.back().Length++;
    }

    EnvironmentStackItem EnvironmentStack::GetValueFromStack(XIndexType IndexInFrame) {
        XIndexType FromStackFrame = FramesInformation.size() - 1;
        while (FromStackFrame > 0 and (FramesInformation[FromStackFrame].Kind == EnvironmentStackFramesInformation::FrameKind::CodeBlockStackFrame)) {
            FromStackFrame--;
        }


        XIndexType RealPos = FramesInformation[FromStackFrame].From + IndexInFrame;
        try {
            return Elements.at(RealPos);
        } catch (std::exception &E) {
            throw;
        }
    }

    void EnvironmentStack::StoreValueToIndex(XIndexType IndexInFrame, EnvironmentStackItem Item) {
        XIndexType FromStackFrame = FramesInformation.size() - 1;
        while (FromStackFrame > 0 and (FramesInformation[FromStackFrame].Kind == EnvironmentStackFramesInformation::FrameKind::CodeBlockStackFrame)) {
            FromStackFrame--;
        }

        XIndexType RealPos = FramesInformation[FromStackFrame].From + IndexInFrame;
        Elements[RealPos] = Item;
    }

    void EnvironmentStack::PushFrame(ProgramCounterInformation Information) {
        FramesInformation.push_back(
                (EnvironmentStackFramesInformation) {EnvironmentStackFramesInformation::FrameKind::CodeBlockStackFrame,
                                                     Elements.size(), 0, Information});
    }

    ProgramCounterInformation EnvironmentStack::PopFrame() {
        ProgramCounterInformation Result{FramesInformation.back().ReturnAddress};
        for (XIndexType I = 0; I < FramesInformation.back().Length; I++) {
            Elements.pop_back();
        }
        FramesInformation.pop_back();
        return Result;
    }

    EnvironmentStack::EnvironmentStack() = default;
} // XScript