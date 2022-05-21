//
// Created by Jerry Chou on 2022/5/7.
//

#ifndef XSCRIPT2_UTILS_HPP
#define XSCRIPT2_UTILS_HPP

#include "Config.hpp"
#include <cstdlib>
#include <cstring>

namespace XScript {
    std::string wstring2string(const std::wstring &ws);

    std::wstring string2wstring(const std::string &s);

    bool IsDigit(wchar_t Char);

    bool IsAlpha(wchar_t Char);

} // XScript

#endif //XSCRIPT2_UTILS_HPP
