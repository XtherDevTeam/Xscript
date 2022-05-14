//
// Created by Jerry Chou on 2022/5/7.
//

#ifndef XSCRIPT2_XSCRIPTEXCEPTION_HPP
#define XSCRIPT2_XSCRIPTEXCEPTION_HPP

#include <exception>

#include "Config.hpp"
#include "Utils.hpp"

namespace XScript {

    class XScriptException : std::exception {
    protected:
        std::string String;
    public:
        XScriptException();

        explicit XScriptException(const XString&  String);

        [[nodiscard]] const char * what() const noexcept override;
    };

} // XScript

#endif //XSCRIPT2_XSCRIPTEXCEPTION_HPP
