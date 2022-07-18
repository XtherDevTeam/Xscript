/*
Localr was under the MIT license.
Copyright(c) 2022 FurryR.
*/

#ifndef XSCRIPT2_LOCALR_HPP
#define XSCRIPT2_LOCALR_HPP

#ifndef _LOCALR_H_
#define _LOCALR_H_

#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
// localr作用域存储了对于字符转换的基本实现。
namespace localr {
    template<typename InternT, typename ExternT>
// codecvt 基类。此基类不包括实现。
    struct codecvt {
        // 输入类型。
        typedef InternT in_type;
        // 输出类型。
        typedef ExternT out_type;

        codecvt() {};

        // 转换src到out_type。
        static out_type in(const in_type &src);

    private:
        // 析构函数。您不可将此类作为变量使用。
        ~codecvt();
    };

    template<>
// codecvt 特化类。负责由宽字符到窄字符的转换。
    struct codecvt<wchar_t, char> {
        // 输入类型。
        typedef wchar_t in_type;
        // 输出类型。
        typedef std::string out_type;

        // 转换src到out_type。
        static out_type in(const in_type &src) {
            static const std::vector<std::pair<unsigned int, unsigned char>> range = {
                    {0x80,       0x00},       // u0000 - u007f
                    {0x800,      0xc0},      // u0080 - u07ff
                    {0x10000,    0xe0},    // u0800 - uffff
                    {0x200000,   0xf0},   // u10000 - u1ffff
                    {0x400000,   0xf8},   // u200000 - u3ffffff
                    {0x80000000, 0xfc}  // u4000000 - u7fffffff
            };
            if (src == 0) return "";
            for (size_t i = 0; i < range.size(); i++) {
                if (src < range[i].first) {
                    wchar_t cp = src;
                    std::string ret(i + 1, '\0');
                    for (size_t j = i; j > 0; j--) {
                        ret[j] = (cp & 0x3f) | 0x80;
                        cp >>= 6;
                    }
                    ret[0] = cp | range[i].second;
                    return ret;
                }
            }
            throw std::invalid_argument("codecvt::in");
        }

        codecvt() {};

    private:
        // 析构函数。您不可将此类作为变量使用。
        ~codecvt();
    };

    template<>
// codecvt 特化类。负责由窄字符到宽字符的转换。
    struct codecvt<char, wchar_t> {
        // 输入类型。
        typedef std::string in_type;
        // 输出类型。
        typedef wchar_t out_type;

        // 转换src到out_type。
        static out_type in(const in_type &src) {
            if (src.empty()) return 0;
            unsigned char b = src[0];
            wchar_t dst;
            if (b < 0x80) {
                if (src.length() == 1) return wchar_t(src[0]);
                throw std::invalid_argument("codecvt::in");
            } else if (b < 0xc0 || b > 0xfd)
                throw std::invalid_argument("codecvt::in");
            else if (b < 0xe0)
                dst = b & 0x1f;
            else if (b < 0xf0)
                dst = b & 0x0f;
            else if (b < 0xf8)
                dst = b & 0x07;
            else if (b < 0xfc)
                dst = b & 0x03;
            else
                dst = b & 0x01;
            for (size_t i = 1; i < src.length(); i++) {
                b = src[i];
                if (b < 0x80 || b > 0xbf) throw std::invalid_argument("codecvt::in");
                dst = (dst << 6) + (src[i] & 0x3f);
            }
            return dst;
        }

        codecvt() {};

    private:
        // 析构函数。您不可将此类作为变量使用。
        ~codecvt();
    };

    template<typename Codecvt>
// string_convert 基类。此基类是序列转换的通用版。
    struct string_convert {
        // 使用的codecvt类型。
        typedef Codecvt codecvt_type;

        // 转换序列src到由Codecvt::out_type组成的序列。
        static std::vector<typename codecvt_type::out_type> in(
                const std::vector<typename codecvt_type::in_type> &src) {
            std::vector<typename Codecvt::out_type> dst;
            for (size_t i = 0; i < src.size(); i++)
                dst.push_back(codecvt_type::in(src[i]));
            return dst;
        };

        string_convert() {};

    private:
        // 析构函数。您不可将此类作为变量使用。
        ~string_convert() {};
    };

    template<>
// string_convert 特化类。负责由宽字符序列到窄字符序列的转换。
    struct string_convert<codecvt<wchar_t, char>> {
        // 使用的codecvt类型。
        typedef codecvt<wchar_t, char> codecvt_type;

        // 转换src到std::string。
        static std::string in(const std::wstring &src) {
            std::string dst;
            for (size_t i = 0; i < src.length(); i++)
                dst += codecvt<wchar_t, char>::in(src[i]);
            return dst;
        }

        string_convert() {};

    private:
        // 析构函数。您不可将此类作为变量使用。
        ~string_convert() {};
    };

    template<>
// string_convert 特化类。负责由窄字符序列到宽字符序列的转换。
    struct string_convert<codecvt<char, wchar_t>> {
        // 使用的codecvt类型。
        typedef codecvt<char, wchar_t> codecvt_type;

        // 转换src到std::wstring。
        static std::wstring in(const std::string &src) {
            std::vector<std::string> t;
            std::wstring dst;
            for (size_t i = 0; i < src.length();) {
                unsigned char b = src[i];
                if (b < 0x80)
                    t.push_back({src[i]}), i++;
                else if (b < 0xc0 || b > 0xfd)
                    throw std::invalid_argument("string_convert::in");  // src is invalid
                else if (b < 0xe0)
                    t.push_back(src.substr(i, 2)), i += 2;
                else if (b < 0xf0)
                    t.push_back(src.substr(i, 3)), i += 3;
                else if (b < 0xf8)
                    t.push_back(src.substr(i, 4)), i += 4;
                else if (b < 0xfc)
                    t.push_back(src.substr(i, 5)), i += 5;
                else
                    t.push_back(src.substr(i, 6)), i += 6;
            }
            for (size_t i = 0; i < t.size(); i++) {
                try {
                    dst += codecvt<char, wchar_t>::in(t[i]);
                } catch (const std::invalid_argument &) {
                    throw std::invalid_argument("string_convert::in");  // src is invalid
                }
            }
            return dst;
        }

        string_convert() {};

    private:
        // 析构函数。您不可将此类作为变量使用。
        ~string_convert() {};
    };
}  // namespace localr
#endif

#endif //XSCRIPT2_LOCALR_HPP
