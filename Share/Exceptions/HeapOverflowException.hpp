//
// Created by Jerry Chou on 2022/5/14.
//

#ifndef XSCRIPT2_HEAPOVERFLOWEXCEPTION_HPP
#define XSCRIPT2_HEAPOVERFLOWEXCEPTION_HPP

#include "../XScriptException.hpp"

namespace XScript {

    class HeapOverflowException : XScriptException {
    public:
        explicit HeapOverflowException(const XString &String);

        [[nodiscard]] const char * what() const noexcept override;
    };

} // XScript

#endif //XSCRIPT2_HEAPOVERFLOWEXCEPTION_HPP
