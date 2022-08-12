//
// Created by Jerry Chou on 2022/5/7.
//

#ifndef XSCRIPT2_UTILS_HPP
#define XSCRIPT2_UTILS_HPP

#include <cstring>
#include <mutex>
#include <filesystem>

#include "Config.hpp"

namespace XScript {
    extern XIndexType CreatedUnfreeElement;

    extern std::mutex InterpreterLock;

    std::string wstring2string(const std::wstring &ws);

    std::wstring string2wstring(const std::string &s);

    std::wstring unescape_string(const std::wstring &s);

    bool IsDigit(wchar_t Char);

    bool IsAlpha(wchar_t Char);

    bool IsHexDigit(wchar_t Char);

    wchar_t ToHexDigit(wchar_t Char);

    XInteger XStringToXInteger(const XString &T);

    XDecimal XStringToXDecimal(const XString &T);

    XIndexType HashBytes(const XBytes& Bytes);

    XIndexType Hash(const XString &T);

    /**
     * Merge R into the back of L
     * @tparam T Original object
     * @param R The Object to merge
     */
    template<typename T>
    void MergeArray(XArray<T> &L, const XArray<T> &R) {
        for (auto &Element: R) {
            L.push_back(Element);
        }
    }

    XArray<XString> SplitStrings(const XString &Str, XCharacter Delim);
} // XScript

#define builtin_hash_code_main (XScript::XIndexType)246720401
#define builtin_hash_code___instruction_add__ (XScript::XIndexType)3311649630992437956
#define builtin_hash_code___instruction_sub__ (XScript::XIndexType)3311649636331619759
#define builtin_hash_code___instruction_mul__ (XScript::XIndexType)3311649634564791843
#define builtin_hash_code___instruction_div__ (XScript::XIndexType)3311649631887487072
#define builtin_hash_code___instruction_logic_and__ (XScript::XIndexType)14644660971655002197
#define builtin_hash_code___instruction_logic_or__ (XScript::XIndexType)16817227887084709089
#define builtin_hash_code___instruction_logic_great_equal__ (XScript::XIndexType)13125448305185876008
#define builtin_hash_code___instruction_logic_less_equal__ (XScript::XIndexType)18431344767761304264
#define builtin_hash_code___instruction_logic_great__ (XScript::XIndexType)1338563774043296927
#define builtin_hash_code___instruction_logic_less__ (XScript::XIndexType)1136736955235993663
#define builtin_hash_code___instruction_indexOf__ (XScript::XIndexType)15638769911280034172
#define builtin_hash_code_super (XScript::XIndexType)34132452939
#define builtin_hash_code___native_library_identifier__ (XScript::XIndexType)5769486266365919877
#define builtin_hash_code___XScriptRuntimeEntry__ (XScript::XIndexType)14066748763523684209

#endif //XSCRIPT2_UTILS_HPP
