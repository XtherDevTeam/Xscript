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
        throw XScript::InternalException(L"Cannot find a local variable named " + Name + L" during compiling");
    }

    void CompilerEnvironment::ImportFromPackage(const XString &FileName) {
        for (auto &PathToSearch: PathsToSearch) {
            XBytes FinalPath = wstring2string(
                    PathToSearch + (PathToSearch.back() == std::filesystem::path::preferred_separator or PathToSearch == L"" ? L"" : (std::wstring){std::filesystem::path::preferred_separator}) + FileName);
            FILE *FilePointer = fopen(FinalPath.c_str(), "rb");
            if (FilePointer == nullptr) {
                continue;
            }
            if (XScript::Reader::BaseTypeReader().ReadIndex(FilePointer) != 0x114514ff2b)
                throw InternalException(L"CompilerEnvironment::ImportFromPackage(): Wrong magic number.");

            // 读取依赖
            XIndexType DependencyNativeClassesCount = XScript::Reader::BaseTypeReader().ReadIndex(FilePointer);
            while (DependencyNativeClassesCount and DependencyNativeClassesCount--) {
                LoadNativeClass(XScript::Reader::BaseTypeReader().ReadString(FilePointer));
            }

            XIndexType DependenciesCount = XScript::Reader::BaseTypeReader().ReadIndex(FilePointer);
            while (DependenciesCount and DependenciesCount--) {
                ImportFromPackage(XScript::Reader::BaseTypeReader().ReadString(FilePointer));
            }

            DependencyPackages.push_back(
                    std::make_pair(FileName, Reader::ExtendedTypeReader().ReadPackageEx(FilePointer)));
            return;
        }
        throw InternalException(L"Cannot open file.");
    }

    std::pair<XIndexType, CompilingTimePackageStructure> CompilerEnvironment::GetPackage(XIndexType Name) {
        XIndexType I = 0;
        for (auto &Index: DependencyPackages) {
            if (Hash(Index.first) == Name)
                return {I, Index.second};
            I++;
        }
        throw XScript::InternalException(
                L"Cannot find a dependency package named " + std::to_wstring(Name) + L" during compiling");
    }

    void CompilerEnvironment::LoadNativeClass(const XString &FileName) {
        for (auto &PathToSearch: PathsToSearch) {
            XString FinalPath =
                    PathToSearch + (PathToSearch.back() == std::filesystem::path::preferred_separator or PathToSearch == L"" ? L"" : (std::wstring){std::filesystem::path::preferred_separator}) + FileName + DynamicLibraryPostfix;
            try {
                NativeLibraries.LoadLib(FinalPath, Hash(FileName));
                DependencyNativeClasses.push_back(FileName);
                return;
            } catch (InternalException &I) {
                continue;
            }
        }
        throw InternalException(L"Cannot open file.");
    }
} // Compiler