//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_PARSEREXCEPTION_HPP
#define XSCRIPT2_PARSEREXCEPTION_HPP

#include "../Utils.hpp"
#include "../XScriptException.hpp"

namespace XScript {

    class ParserException : XScriptException {
        std::string message;
    public:
        ParserException();

        ParserException(XInteger Line, XInteger Column, const XString &Reason);

        [[nodiscard]] const char *what() const noexcept override;
    };

} // XScript

#endif //XSCRIPT2_PARSEREXCEPTION_HPP
