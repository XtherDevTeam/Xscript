//
// Created by Jerry Chou on 2022/5/20.
//

#include "BasicTestFramework.hpp"

namespace XScript {
    namespace Instance {

        BasicTestFramework::BasicTestFramework() : Interpreter(InterpreterEnvironment) {
            InterpreterEnvironment.Stack.FramesInformation.push_back((EnvironmentStackFramesInformation) {
                    EnvironmentStackFramesInformation::FrameKind::FunctionStackFrame, 0, 0, {}});

            InterpreterEnvironment.ProgramCounter = (ProgramCounterInformation){Commands};
        }

        void BasicTestFramework::Run() {
            Interpreter.MainLoop();
        }
    } // XScript
} // Instance