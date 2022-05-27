//
// Created by Jerry Chou on 2022/5/14.
//

#ifndef XSCRIPT2_BYTECODEINTERPRETERROR_HPP
#define XSCRIPT2_BYTECODEINTERPRETERROR_HPP

#include "../XScriptException.hpp"

namespace XScript {

    class BytecodeInterpretError : XScriptException {
    public:
        explicit BytecodeInterpretError(const XString &String);

        [[nodiscard]] const char * what() const noexcept override;
    };

} // XScript

#endif //XSCRIPT2_BYTECODEINTERPRETERROR_HPP
