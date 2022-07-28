//
// Created by Jerry Chou on 2022/5/7.
//

#ifndef XSCRIPT2_UTILS_HPP
#define XSCRIPT2_UTILS_HPP

#include <cstring>

#include "Config.hpp"

namespace XScript {
    std::string wstring2string(const std::wstring &ws);

    std::wstring string2wstring(const std::string &s);

    std::wstring unescape_string(const std::wstring &s);

    bool IsDigit(wchar_t Char);

    bool IsAlpha(wchar_t Char);

    bool IsHexDigit(wchar_t Char);

    wchar_t ToHexDigit(wchar_t Char);

    XInteger XStringToXInteger(const XString &T);

    XDecimal XStringToXDecimal(const XString &T);

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

#define builtin_hash_code_main 7670424507768520307
#define builtin_hash_code___instruction_add__ 7874026003045742965
#define builtin_hash_code___instruction_sub__ 11838334185600141604
#define builtin_hash_code___instruction_mul__ 17051752587414762514
#define builtin_hash_code___instruction_div__ 273068164101398817
#define builtin_hash_code___instruction_logic_and__ 14644660971655002197
#define builtin_hash_code___instruction_logic_or__ 3017265981745465542
#define builtin_hash_code___instruction_logic_great_equal__ 17418077302597999929
#define builtin_hash_code___instruction_logic_less_equal__ 1006925257097887696
#define builtin_hash_code___instruction_logic_great__ 11341168425154990597
#define builtin_hash_code___instruction_logic_less__ 2266364071854114079
#define builtin_hash_code___instruction_indexOf__ 14024942792811143289
#define builtin_hash_code_super 6513641090864109706
#define builtin_hash_code___native_library_identifier__ 14012857459599550780
#define builtin_hash_code___XScriptRuntimeEntry__ 2591539125669357027


#endif //XSCRIPT2_UTILS_HPP
