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

        if (IsMainPackage) {
            MainPackage = Reader::ExtendedTypeReader().ReadPackage(FilePointer);
        } else {
            DependencyPackages[Hash(PackageName)] = Reader::ExtendedTypeReader().ReadPackage(FilePointer);
            /* 设置依赖包中函数的包ID */
            for (auto &Function : DependencyPackages[Hash(PackageName)].FunctionPool) {
                Function.second.PackageID = Hash(PackageName);
            }
        }
        /* 在启动虚拟机时执行初始化包代码 */
    }
} // XScript