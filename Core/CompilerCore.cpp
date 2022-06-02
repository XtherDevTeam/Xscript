//
// Created by Jerry Chou on 2022/5/29.
//

#include <iostream>
#include "CompilerCore.hpp"
#include "../Frontend/Lexer.hpp"
#include "../Frontend/AST.hpp"
#include "../Backend/Compiler/FileCompiler.hpp"
#include "../Frontend/Parsers/FileNodeGenerator.hpp"
#include "../Share/Exceptions/InternalException.hpp"

namespace XScript {
    void CompileForFile(XScript::Compiler::CompilerEnvironment &Environment, const XScript::XString &FilePath) {
        FILE *FilePointer = fopen(XScript::wstring2string(FilePath).c_str(), "r+");
        if (FilePointer == nullptr) {
            throw InternalException(L"CompileForFile(): Cannot open file");
        }
        XScript::XString Str;
        XScript::XBytes Dest;
        XScript::XIndexType ReadCount = 0;
        Dest.resize(1024);
        while (fread(Dest.data(), 1, 1024, FilePointer) > 0) {
            std::wcout << std::to_wstring(Dest.find('\0')) << std::endl;
            if (!Dest.find('\0'))
                break;
            Dest.resize(Dest.find('\0'));
            Str += XScript::string2wstring(Dest);
            Dest = "";
            Dest.resize(1024);
        }

        XScript::Lexer Lex{Str};
        Lex.Scan();

        XScript::AST FileTree = XScript::Generator::FileNodeGenerator(Lex).Parse();
        MergeArray(Environment.MainPackage.PackageInitializeCodes,
                   XScript::Compiler::FileCompiler(Environment).GenerateForFile(FileTree));
    }

}