//
// Created by Jerry Chou on 2022/5/7.
//

#include <sstream>
#include "Utils.hpp"

#include "../ThirdPartyLibraries/localr.hpp"

namespace XScript {
    std::string wstring2string(const std::wstring &ws) {
        return localr::string_convert<localr::codecvt<wchar_t, char>>::in(ws);
    }

    std::wstring string2wstring(const std::string &s) {
        return localr::string_convert<localr::codecvt<char, wchar_t>>::in(s);
    }

    bool IsDigit(wchar_t Char) {
        return (Char >= L'0' && Char <= L'9');
    }

    bool IsAlpha(wchar_t Char) {
        return ((Char >= L'A' && Char <= L'Z') || (Char >= L'a' && Char <= 'z') || Char == L'_' || Char == L'@');
    }

    XInteger XStringToXInteger(const XString &T) {
        char *MakeStdlibHappyXD;
        const std::string P = wstring2string(T);
        return strtol(P.data(), &MakeStdlibHappyXD, 10);
    }

    XDecimal XStringToXDecimal(const XString &T) {
        char *MakeStdlibHappyXD;
        const std::string P = wstring2string(T);
        return strtof(P.data(), &MakeStdlibHappyXD);
    }

    XIndexType Hash(const XString &T) {
        return std::hash<XString>()(T);
    }

    XArray<XString> SplitStrings(const XString &Str, XCharacter Delim) {
        XArray<XString> result;
        std::wstringstream ss(Str);
        XString item;
        while (getline(ss, item, Delim)) {
            result.push_back(item);
        }
        return result;
    }


} // XScript