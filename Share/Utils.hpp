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

#if defined(__WIN32)
#define builtin_hash_code_main (XScript::XIndexType)9328764686893287123
#define builtin_hash_code___instruction_add__ (XScript::XIndexType)15666197330935411857
#define builtin_hash_code___instruction_sub__ (XScript::XIndexType)16920049096241614577
#define builtin_hash_code___instruction_mul__ (XScript::XIndexType)13912836029130607537
#define builtin_hash_code___instruction_div__ (XScript::XIndexType)2588076979984842845
#define builtin_hash_code___instruction_logic_and__ (XScript::XIndexType)7124057605393048397
#define builtin_hash_code___instruction_logic_or__ (XScript::XIndexType)12949669326930031122
#define builtin_hash_code___instruction_logic_great_equal__ (XScript::XIndexType)1198041032740863977
#define builtin_hash_code___instruction_logic_less_equal__ (XScript::XIndexType)16404804629521996931
#define builtin_hash_code___instruction_logic_great__ (XScript::XIndexType)13338539619241891218
#define builtin_hash_code___instruction_logic_less__ (XScript::XIndexType)296125903598827187
#define builtin_hash_code___instruction_indexOf__ (XScript::XIndexType)10918802888327628437
#define builtin_hash_code_super (XScript::XIndexType)3155968044394352334
#define builtin_hash_code___native_library_identifier__ (XScript::XIndexType)18070401361008655398
#define builtin_hash_code___XScriptRuntimeEntry__ (XScript::XIndexType)7217704021400880566
#elif defined(__linux__)
#define builtin_hash_code_main (XScript::XIndexType)7670424507768520307
#define builtin_hash_code___instruction_add__ (XScript::XIndexType)7874026003045742965
#define builtin_hash_code___instruction_sub__ (XScript::XIndexType)11838334185600141604
#define builtin_hash_code___instruction_mul__ (XScript::XIndexType)17051752587414762514
#define builtin_hash_code___instruction_div__ (XScript::XIndexType)273068164101398817
#define builtin_hash_code___instruction_logic_and__ (XScript::XIndexType)14644660971655002197
#define builtin_hash_code___instruction_logic_or__ (XScript::XIndexType)3017265981745465542
#define builtin_hash_code___instruction_logic_great_equal__ (XScript::XIndexType)17418077302597999929
#define builtin_hash_code___instruction_logic_less_equal__ (XScript::XIndexType)1006925257097887696
#define builtin_hash_code___instruction_logic_great__ (XScript::XIndexType)11341168425154990597
#define builtin_hash_code___instruction_logic_less__ (XScript::XIndexType)2266364071854114079
#define builtin_hash_code___instruction_indexOf__ (XScript::XIndexType)14024942792811143289
#define builtin_hash_code_super (XScript::XIndexType)6513641090864109706
#define builtin_hash_code___native_library_identifier__ (XScript::XIndexType)14012857459599550780
#define builtin_hash_code___XScriptRuntimeEntry__ (XScript::XIndexType)2591539125669357027
#elif defined(__APPLE__)
#define builtin_hash_code_main (XScript::XIndexType)17299091360650233103
#define builtin_hash_code___instruction_add__ (XScript::XIndexType)10464478314076775309
#define builtin_hash_code___instruction_sub__ (XScript::XIndexType)1222037404924959291
#define builtin_hash_code___instruction_mul__ (XScript::XIndexType)15504539509551616032
#define builtin_hash_code___instruction_div__ (XScript::XIndexType)3783435002672145191
#define builtin_hash_code___instruction_logic_and__ (XScript::XIndexType)17172099155340832562
#define builtin_hash_code___instruction_logic_or__ (XScript::XIndexType)8726144604230437156
#define builtin_hash_code___instruction_logic_great_equal__ (XScript::XIndexType)16337795713401796158
#define builtin_hash_code___instruction_logic_less_equal__ (XScript::XIndexType)2230942099143076960
#define builtin_hash_code___instruction_logic_great__ (XScript::XIndexType)17026838180953254426
#define builtin_hash_code___instruction_logic_less__ (XScript::XIndexType)1790909244707514774
#define builtin_hash_code___instruction_indexOf__ (XScript::XIndexType)8279956869312200099
#define builtin_hash_code_super (XScript::XIndexType)12255509608937990104
#define builtin_hash_code___native_library_identifier__ (XScript::XIndexType)17994388048575125041
#define builtin_hash_code___XScriptRuntimeEntry__ (XScript::XIndexType)1154313383859417322
#endif

#endif //XSCRIPT2_UTILS_HPP
