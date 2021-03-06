//
// Created by Jerry Chou on 2022/5/21.
//

#include "InternalException.hpp"

namespace XScript {
    InternalException::InternalException(const XString &Str) : XScriptException(Str) {

    }

    const char *InternalException::what() const noexcept {
        return XScriptException::what();
    }
} // XScript