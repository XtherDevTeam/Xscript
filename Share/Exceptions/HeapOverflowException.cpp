//
// Created by Jerry Chou on 2022/5/14.
//

#include "HeapOverflowException.hpp"

namespace XScript {
    HeapOverflowException::HeapOverflowException(const XString &String) : XScriptException(
            L"HeapOverflowException: " + String) {

    }

    const char *HeapOverflowException::what() const noexcept {
        return XScriptException::what();
    }
} // XScript