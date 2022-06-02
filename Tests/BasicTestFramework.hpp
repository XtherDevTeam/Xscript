//
// Created by Jerry Chou on 2022/5/20.
//

#ifndef XSCRIPT2_BASICTESTFRAMEWORK_HPP
#define XSCRIPT2_BASICTESTFRAMEWORK_HPP

#include "../Executor/BytecodeInterpreter.hpp"

namespace XScript::Instance {

    class BasicTestFramework {
    public:
        BytecodeInterpreter Interpreter;
        Environment InterpreterEnvironment;
        XArray<BytecodeStructure> Commands;

        BasicTestFramework();

        void Run();
    };

} // Instance

#endif //XSCRIPT2_BASICTESTFRAMEWORK_HPP
