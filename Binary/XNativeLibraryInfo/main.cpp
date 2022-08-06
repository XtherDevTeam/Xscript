//
// Created by Jerry Chou on 22-7-18.
//
#include <iostream>

#include "../../Frontend/Lexer.hpp"
#include "../../Share/Exceptions/InternalException.hpp"
#include "../../Share/Exceptions/CompilerError.hpp"
#include "../../Share/Exceptions/ParserException.hpp"
#include "../../Core/CompilerCore.hpp"
#include "../../Executor/Executor.hpp"

using namespace XScript;

XMap<XString, XString> Arguments;

void ParseArguments(int argc, const char **argv) {
    /* defaults */
    Arguments[L"PATH"] = (XString){L".;"};
    for (int i = 1; i < argc; i++) {
        XString Str = string2wstring(argv[i]);
        XIndexType Equ = Str.find(L'=');
        if (Equ != XString::npos) {
            XString L = Str.substr(0, Equ);
            XString R = Str.substr(Equ + 1);
            if (L[0] == L'\'' || L[0] == L'"') {
                L = L.substr(1, L.size() - 2);
            }
            if (R[0] == L'\'' || R[0] == L'"') {
                R = R.substr(1, R.size() - 2);
            }

            Arguments[L] = R;
        } else {
            throw InternalException(L"Invalid param: " + Str);
        }
    }
}

int main(int argc, const char **argv) {
    try {
        ParseArguments(argc, argv);
        NativeLibrariesManager Manger;
        Manger.LoadLib(Arguments[L"file"], 0);
        auto &Inf = Manger[0].Information;
        std::cout << "XNL File information for " << wstring2string(Arguments[L"file"]) << std::endl;
        std::cout << "File author: " << wstring2string(Inf.Author) << std::endl;
        std::cout << "File description: " << wstring2string(Inf.Description) << std::endl;
        std::cout << "Classes: " << std::endl;
        for (auto &I : Inf.Classes) {
            std::cout << "\t" << wstring2string(I.second.ClassName) << std::endl;
            std::cout << "\t\tMethods: " << std::endl;
            for (auto &J : I.second.Methods) {
                std::cout << "\t\t\t" << std::to_string(J.first) << ":" << std::endl;
                std::cout << "\t\t\t\t Recommend param count: " << std::to_string(J.second.ParamsCount) << std::endl;
            }
        }
    } catch (InternalException &E) {
        std::cerr << E.what() << "\n" << std::flush;
    } catch (BytecodeInterpretError &E) {
        std::cerr << E.what() << "\n" << std::flush;
    }
    return 0;
}