//
// Created by Jerry Chou on 2022/5/21.
//

#include "CompilerEnvironment.hpp"
#include "../Share/Exceptions/InternalException.hpp"
#include "../Core/Reader/BaseTypeReader.hpp"
#include "../Core/Reader/ExtendedTypeReader.hpp"

namespace XScript::Compiler {
    XIndexType CompilerEnvironment::PushLocal(const XString &Name, const SymbolItem &Item) {
        Locals.push_back(std::make_pair(Name, Item));
        return Locals.size() - 1;
    }

    std::pair<XIndexType, SymbolItem> CompilerEnvironment::GetLocal(const XString &Name) {
        XIndexType I = 0;
        for (auto &Index: Locals) {
            if (Index.first == Name)
                return {I, Index.second};
            I++;
        }
        throw XScript::InternalException(L"Cannot find a local variable named " + Name + L" while compiling");
    }

    void CompilerEnvironment::ImportFromPackage(const XString& FileName) {
        for (auto &PathToSearch : PathsToSearch) {
            XBytes FinalPath = wstring2string(PathToSearch + L"/" + FileName);
            FILE *FilePointer = fopen(FinalPath.c_str(), "r+");
            if (FilePointer == nullptr) {
                throw InternalException(L"Cannot open file.");
            }
            if (XScript::Reader::BaseTypeReader().ReadIndex(FilePointer) != 0x114514ff2b)
                throw InternalException(L"CompilerEnvironment::ImportFromPackage(): Wrong magic number.");

            DependencyPackages[Hash(FileName)] = std::make_pair(FileName, Reader::ExtendedTypeReader().ReadPackageEx(FilePointer));
        }
    }
} // Compiler