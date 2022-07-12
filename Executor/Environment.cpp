//
// Created by Jerry Chou on 2022/5/13.
//

#include "Environment.hpp"
#include "../Share/Exceptions/InternalException.hpp"
#include "../Core/Reader/ExtendedTypeReader.hpp"
#include "../Core/Reader/BaseTypeReader.hpp"

namespace XScript {
    void Environment::LoadFromFile(const XString &FilePath, const XString& PackageName, bool IsMainPackage) {
        XBytes FinalPath = wstring2string(FilePath);
        FILE *FilePointer = fopen(FinalPath.c_str(), "r+");
        if (FilePointer == nullptr) {
            throw InternalException(L"Environment::LoadFromFile() : Cannot open file.");
        }
        if (Reader::BaseTypeReader().ReadIndex(FilePointer) != 0x114514ff2b) {
            throw InternalException(L"Environment::LoadFromFile() : Wrong magic number. (MagicNumber != 0x114514ff2b)");
        }

        /* 加载依赖 */
        XArray<XString> DependPackages = Reader::ExtendedTypeReader().ReadStringArray(FilePointer);
        for (auto &Package: DependPackages) {
            for (auto &Prefix: PathsToSearch) {
                LoadFromFile(Prefix + (Prefix.back() == L'/' ? L"" : L"/") + Package, Package,false);
            }
        }

        XIndexType PkgID = Hash(PackageName);
        if (IsMainPackage) {
            Packages[PkgID] = Reader::ExtendedTypeReader().ReadPackage(FilePointer);
            if (!Packages[PkgID].FunctionPool.count(Hash(L"main")))
                throw InternalException(L"Environment::LoadFromFile() : Cannot find __XScriptRuntimeEntry__() function for entry.");

            for (auto &Function : Packages[Hash(PackageName)].FunctionPool) {
                Function.second.PackageID = PkgID;
            }

            /* 设置加载顺序 在启动虚拟机时执行初始化包代码 **主包最后加载** */
            LoadedPackageIDs.push_back(PkgID);
        } else {
            Packages[PkgID] = Reader::ExtendedTypeReader().ReadPackage(FilePointer);
            /* 设置依赖包中函数的包ID */
            for (auto &Function : Packages[PkgID].FunctionPool) {
                Function.second.PackageID = PkgID;
            }

            /* 设置加载顺序 在启动虚拟机时执行初始化包代码 */
            LoadedPackageIDs.push_back(PkgID);
        }
    }
} // XScript