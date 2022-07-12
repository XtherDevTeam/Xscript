//
// Created by Jerry Chou on 2022/5/14.
//

#include "BytecodeInterpretError.hpp"

namespace XScript {
    BytecodeInterpretError::BytecodeInterpretError(const XString &String) : XScriptException(String) {

    }

    const char *BytecodeInterpretError::what() const noexcept {
        return XScriptException::what();
    }
} // XScript