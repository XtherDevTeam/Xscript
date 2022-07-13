#include <iostream>

/* XScript 2 Project includes */
#include "Tests/BasicTests.hpp"
#include "Frontend/Lexer.hpp"
#include "Share/Exceptions/InternalException.hpp"
#include "Share/Exceptions/CompilerError.hpp"
#include "Share/Exceptions/ParserException.hpp"
#include "Core/CompilerCore.hpp"
#include "Executor/Executor.hpp"


int main(int argc, const char **argv) {
    std::wcout << L"[XScript 2 Early Test] Demo developed by Jerry Chou (Winghong Zau)\n";

    if (argc == 2 && XScript::XBytes{argv[1]} == "ci") {
        std::cout << "CI detected, skipped.\n";
        return 0;
    } else if (argc == 2 && XScript::XBytes{argv[1]} == "vm") {
        std::wcout << L"XScript Program Executor Early Test\n";
        XScript::Executor Executor;
        Executor.VM.PathsToSearch.push_back(L".");

        std::wcout << L"Input package filename.\n";
        XScript::XString PkgFilePath;
        std::wcout << L"(filename) ";
        std::wcin >> PkgFilePath;

        Executor.Load(PkgFilePath);
        Executor.Init();
        XScript::XIndexType Duration = Executor.StartWithRuntimeDuration();
        std::wcout << L"Executing duration: " << Duration << "ms\n";
        return 0;
    }
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

        std::wcout << L"Input compiler flags and type 'End' and press Enter to stop input.\n";
        while (true) {
            XScript::XString Temp;
            std::wcout << L"(flag) ";
            std::wcin >> Temp;
            if (Temp == L"End")
                break;
            if (!Temp.empty())
                Environ.CompilerFlags.push_back(Temp);
        }

        for (auto &I : FilesToCompile) {
            XScript::CompileForFile(Environ, I);
        }

        XScript::XString OutputFilename;
        std::wcout << L"(output filename) ";
        std::wcin >> OutputFilename;
        XScript::OutputBinary(Environ, OutputFilename);
    } catch (XScript::ParserException &E) {
        std::wcerr << E.what() << std::endl;
    } catch (XScript::CompilerError &E) {
        std::wcerr << E.what() << std::endl;
    } catch (XScript::LexerException &E) {
        std::wcerr << E.what() << std::endl;
    } catch (XScript::InternalException &E) {
        std::wcerr << E.what() << std::endl;
    }
    return 0;
}
