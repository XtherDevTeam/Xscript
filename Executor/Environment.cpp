//
// Created by Jerry Chou on 2022/5/13.
//

#include "Environment.hpp"
#include "../Share/Exceptions/InternalException.hpp"
#include "../Core/Reader/ExtendedTypeReader.hpp"
#include "../Core/Reader/BaseTypeReader.hpp"

namespace XScript {
    void Environment::LoadFromFile(const XString &FilePath, const XString &PackageName, bool IsMainPackage) {
        XBytes FinalPath = wstring2string(FilePath);
        FILE *FilePointer = fopen(FinalPath.c_str(), "r+");
        if (FilePointer == nullptr) {
            throw InternalException(L"Environment::LoadFromFile() : Cannot open file.");
        }
        if (Reader::BaseTypeReader().ReadIndex(FilePointer) != 0x114514ff2b) {
            throw InternalException(L"Environment::LoadFromFile() : Wrong magic number. (MagicNumber != 0x114514ff2b)");
        }


        /* 加载依赖 */
        XArray<XString> DependNativeClasses = Reader::ExtendedTypeReader().ReadStringArray(FilePointer);
        for (auto &Class: DependNativeClasses) {
            bool LoadFail = true;

            for (auto &Prefix: PathsToSearch) {
                XString FFF = Prefix + (Prefix.back() == L'/' or Prefix == L"" ? L"" : L"/") + Class + DynamicLibraryPostfix;
                try {
                    NativeLibraries.LoadLib(FFF, Hash(Class));
                    LoadFail = false;
                    break;
                } catch (InternalException &E) {
                    continue;
                }
            }

            if (LoadFail)
                throw InternalException(L"Environment::LoadFromFile() : Cannot open native library.");
        }

        XArray<XString> DependPackages = Reader::ExtendedTypeReader().ReadStringArray(FilePointer);
        for (auto &Package: DependPackages) {
            bool LoadFail = true;

            for (auto &Prefix: PathsToSearch) {
                XString FFF = Prefix + (Prefix.back() == L'/' or Prefix == L"" ? L"" : L"/") + Package;
                FILE *IsExist = fopen(wstring2string(FFF).c_str(), "rb+");
                if (IsExist == nullptr)
                    continue;
                fclose(IsExist);

                LoadFromFile(FFF, Package, false);
                LoadFail = false;
                break;
            }

            if (LoadFail)
                throw InternalException(L"Environment::LoadFromFile() : Cannot open file.");
        }


        XIndexType PkgID = Hash(PackageName);
        if (IsMainPackage) {
            Packages[PkgID] = Reader::ExtendedTypeReader().ReadPackage(FilePointer);
            if (!Packages[PkgID].FunctionPool.count(builtin_hash_code_main))
                throw InternalException(
                        L"Environment::LoadFromFile() : Cannot find __XScriptRuntimeEntry__() function for entry.");

            for (auto &Function: Packages[Hash(PackageName)].FunctionPool) {
                Function.second.PackageID = PkgID;
            }

            /* 设置加载顺序 在启动虚拟机时执行初始化包代码 **主包最后加载** */
            LoadedPackageIDs.push_back(PkgID);
        } else {
            Packages[PkgID] = Reader::ExtendedTypeReader().ReadPackage(FilePointer);
            /* 设置依赖包中函数的包ID */
            for (auto &Function: Packages[PkgID].FunctionPool) {
                Function.second.PackageID = PkgID;
            }

            /* 设置加载顺序 在启动虚拟机时执行初始化包代码 */
            LoadedPackageIDs.push_back(PkgID);
        }
    }

} // XScript