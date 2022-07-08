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
#include "Serializatior/BaseTypeSerializatior.hpp"
#include "Serializatior/ExtendedTypeSerializatior.hpp"

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

    void OutputBinary(Compiler::CompilerEnvironment &Environment, const XString &FilePath) {
        FILE *FilePointer = fopen(XScript::wstring2string(FilePath).c_str(), "w+");
        XIndexType MagicNumber = 0x114514ff2b;
        Serializatior::BaseTypeSerializatior()(FilePointer, MagicNumber);
        /* 写入依赖 */
        Serializatior::BaseTypeSerializatior()(FilePointer, static_cast<XIndexType>(Environment.DependencyPackages.size()));
        for (auto &I:Environment.DependencyPackages) {
            Serializatior::BaseTypeSerializatior()(FilePointer, GetFilenameFromPath(I.first));
        }
        /* 写入主包 */
        Serializatior::ExtendedTypeSerializatior()(FilePointer, Environment.MainPackage);

        fclose(FilePointer);
    }

    XString GetFilenameFromPath(const XString &Filepath) {
        XIndexType From = Filepath.rfind('/');
        if (From == XString::npos)
            From = Filepath.rfind('\\');
        if (From == XString::npos)
            return L"";
        return Filepath.substr(From);
    }

}