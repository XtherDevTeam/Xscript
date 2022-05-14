//
// Created by Jerry Chou on 2022/5/14.
//

#ifndef XSCRIPT2_BYTECODEINTERPRETERROR_HPP
#define XSCRIPT2_BYTECODEINTERPRETERROR_HPP

#include "../XScriptException.hpp"

namespace XScript {

    class BytecodeInterpretError : XScriptException {
    public:
        BytecodeInterpretError(const XString &String);
    };

} // XScript

#endif //XSCRIPT2_BYTECODEINTERPRETERROR_HPP
