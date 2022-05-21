//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_COMPILERERROR_HPP
#define XSCRIPT2_COMPILERERROR_HPP

#include "../XScriptException.hpp"

namespace XScript {

    class CompilerError : XScriptException {
    public:
        CompilerError(XIndexType Line, XIndexType Col, const XString& Text);
    };

} // XScript

#endif //XSCRIPT2_COMPILERERROR_HPP
