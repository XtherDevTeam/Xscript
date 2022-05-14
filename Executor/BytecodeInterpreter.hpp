//
// Created by Jerry Chou on 2022/5/14.
//

#ifndef XSCRIPT2_BYTECODEINTERPRETER_HPP
#define XSCRIPT2_BYTECODEINTERPRETER_HPP

#include "Environment.hpp"
#include "../Share/Exceptions/BytecodeInterpretError.hpp"

namespace XScript {

    class BytecodeInterpreter {
    public:
        Environment &InterpreterEnvironment;

        BytecodeInterpreter(Environment &interpreterEnvironment);

        void MainLoop();
    };

} // XScript

#endif //XSCRIPT2_BYTECODEINTERPRETER_HPP
