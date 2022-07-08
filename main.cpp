#include <iostream>

/* XScript 2 Project includes */
#include "Tests/BasicTests.hpp"
#include "Frontend/Lexer.hpp"
#include "Share/Exceptions/InternalException.hpp"
#include "Share/Exceptions/CompilerError.hpp"
#include "Share/Exceptions/ParserException.hpp"
#include "Core/CompilerCore.hpp"


int main(int argc, const char **argv) {
    if (argc == 2 && XScript::XBytes{argv[1]} == "ci") {
        std::cout << "CI detected, skipped.\n";
        return 0;
    }
    std::wcout << L"[XScript 2 Early Test] Demo developed by Jerry Chou (Winghong Zau)\n";
    std::wcout << L"Input filenames to compile and type 'End' and press Enter to stop input.\n";
    XScript::XArray<XScript::XString> FilesToCompile;
    while (true) {
        XScript::XString Temp;
        std::wcout << L"(filename) ";
        std::wcin >> Temp;
        if (Temp == L"End")
            break;
        if (!Temp.empty())
            FilesToCompile.push_back(Temp);
    }
    try {
        XScript::Compiler::CompilerEnvironment Environ{};

        for (auto &I : FilesToCompile) {
            XScript::CompileForFile(Environ, I);
        }

        XScript::XString OutputFilename;
        std::wcout << L"(output filename) ";
        std::wcin >> OutputFilename;
        XScript::OutputBinary(Environ, OutputFilename);
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
