//
// Created by Jerry Chou on 2022/5/7.
//

#include <sstream>
#include "Utils.hpp"

#include "../ThirdPartyLibraries/localr.hpp"

namespace XScript {
    XIndexType CreatedUnfreeElement;

    std::mutex InterpreterLock;

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
        char *MakeStdlibHappyXD = nullptr;
        const std::string P = wstring2string(T);
        return strtol(P.data(), &MakeStdlibHappyXD, 10);
    }

    XDecimal XStringToXDecimal(const XString &T) {
        char *MakeStdlibHappyXD = nullptr;
        const std::string P = wstring2string(T);
        return strtof(P.data(), &MakeStdlibHappyXD);
    }

    XIndexType Hash(const XString &T) {
        return HashBytes(wstring2string(T));
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

    std::wstring unescape_string(const std::wstring &s) {
        std::wstring output;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '\\') {
                i++;
                switch (s[i]) {
                    case L'"':
                        output += L'"';
                        break;
                    case L'\'':
                        output += L'\'';
                        break;
                    case L'\\':
                        output += L'\\';
                        break;
                    case L'b':
                        output += L'\b';
                        break;
                    case L'f':
                        output += L'\f';
                        break;
                    case L'n':
                        output += L'\n';
                        break;
                    case L'r':
                        output += L'\r';
                        break;
                    case L't':
                        output += L'\t';
                        break;
                    default:
                        return L"";
                }
            } else {
                output += s[i];
            }
        }
        return output;
    }

    bool IsHexDigit(wchar_t Char) {
        if (Char >= '0' and Char <= '9')
            return true;
        if (Char >= 'a' and Char <= 'f')
            return true;
        if (Char >= 'A' and Char <= 'F')
            return true;

        return false;
    }

    wchar_t ToHexDigit(wchar_t Char) {
        if (Char >= '0' and Char <= '9')
            return Char - '0';
        if (Char >= 'a' and Char <= 'f')
            return Char - 'a' + 10;
        if (Char >= 'A' and Char <= 'F')
            return Char - 'A' + 10;

        return 0;
    }

    XIndexType HashBytes(const XBytes &Bytes) {
        XIndexType result = 0;
        for (char Byte : Bytes) {
            result = (result * 131) + Byte;
        }
        return result;
    }


} // XScript