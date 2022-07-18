//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_COMPILERENVIRONMENT_HPP
#define XSCRIPT2_COMPILERENVIRONMENT_HPP

#include "../Share/Config.hpp"
#include "SymbolItem.hpp"
#include "CompilingTimePackageStructure.hpp"
#include "../NativeLibrary/NativeLibrariesManager.hpp"

namespace XScript::Compiler {

    class CompilerEnvironment {
    public:
        XIndexType InWhichPackage;

        XArray<XString> PathsToSearch;

        XArray<XString> CompilerFlags;

        XArray<XString> DependencyNativeClasses;

        NativeLibrariesManager NativeLibraries;

        CompilingTimePackageStructure MainPackage;

        XArray<std::pair<XString, CompilingTimePackageStructure>> DependencyPackages;

        XArray<std::pair<XString, SymbolItem>> Locals;

        void ImportFromPackage(const XString &FileName);

        void LoadNativeClass(const XString &FileName);

        XIndexType PushLocal(const XString &Name, const SymbolItem &Item);

        std::pair<XIndexType, SymbolItem> GetLocal(const XString &Name);

        std::pair<XIndexType, CompilingTimePackageStructure> GetPackage(XIndexType Name);
    };

} // Compiler

#endif //XSCRIPT2_COMPILERENVIRONMENT_HPP
