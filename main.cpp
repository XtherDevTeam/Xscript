#include <iostream>

/* XScript 2 Project includes */
#include "Tests/BasicTests.hpp"
#include "Frontend/Lexer.hpp"
#include "Share/Exceptions/InternalException.hpp"
#include "Share/Exceptions/CompilerError.hpp"
#include "Share/Exceptions/ParserException.hpp"
#include "Core/CompilerCore.hpp"


int main() {
    std::wcout << L"[XScript 2 Early Test] Demo developed by Jerry Chou (Winghong Zau)\n";
    std::wcout << L"Input filenames to compile and press ^D or ^Z + Enter to stop input.\n";
    XScript::XArray<XScript::XString> FilesToCompile;
    while (!std::wcin.eof()) {
        XScript::XString Temp;
        std::wcout << L"(filename) ";
        std::wcin >> Temp;
        if (!Temp.empty())
            FilesToCompile.push_back(Temp);
    }
    try {
        XScript::Compiler::CompilerEnvironment Environ{};
        for (auto &Filename: FilesToCompile) {
            XScript::CompileForFile(Environ, Filename);
        }
        for (auto &Instruction: Environ.MainPackage.Functions.back().second.BytecodeArray) {
            std::wcout << Instruction.ToString() << std::endl;
        }
    } catch (XScript::ParserException &E) {
        std::cout << E.what() << std::endl;
    } catch (XScript::CompilerError &E) {
        std::cout << E.what() << std::endl;
    } catch (XScript::LexerException &E) {
        std::cout << E.what() << std::endl;
    } catch (XScript::InternalException &E) {
        std::cout << E.what() << std::endl;
    }
    return 0;
}
