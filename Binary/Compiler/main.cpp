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
    Arguments[L"PATH"] = L".;";
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
        XScript::Compiler::CompilerEnvironment Environ{};
        Environ.PathsToSearch = SplitStrings(Arguments[L"PATH"], L';');
        Environ.CompilerFlags = SplitStrings(Arguments[L"flags"], L';');
        if (!Arguments.count(L"in") || !Arguments.count(L"out")) {
            throw InternalException(L"Could not find input filename or output filename in given params.");
        }
        for (auto &File: SplitStrings(Arguments[L"in"], L';')) {
            XScript::CompileForFile(Environ, File);
        }
        XScript::OutputBinary(Environ, Arguments[L"out"]);
    } catch (ParserException &E) {
        std::cerr << E.what() << "\n" << std::flush;
    } catch (InternalException &E) {
        std::cerr << E.what() << "\n" << std::flush;
    } catch (CompilerError &E) {
        std::cerr << E.what() << "\n" << std::flush;
    }
    return 0;
}