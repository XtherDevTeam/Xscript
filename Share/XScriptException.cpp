//
// Created by Jerry Chou on 2022/5/7.
//

#include "XScriptException.hpp"

namespace XScript {
    XScriptException::XScriptException(const XString &String) : String(wstring2string(String)) {

    }

    const char *XScriptException::what() const noexcept {
        return String.c_str();
    }

    XScriptException::XScriptException() = default;
} // XScript