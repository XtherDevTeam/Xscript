//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_INTERNALEXCEPTION_HPP
#define XSCRIPT2_INTERNALEXCEPTION_HPP

#include "../XScriptException.hpp"

namespace XScript {

    class InternalException : XScriptException {
    public:
        explicit InternalException(const XString &Str);

        [[nodiscard]] const char *what() const noexcept override;
    };

} // XScript

#endif //XSCRIPT2_INTERNALEXCEPTION_HPP
