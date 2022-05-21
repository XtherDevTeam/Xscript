//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_COMPILERENVIRONMENT_HPP
#define XSCRIPT2_COMPILERENVIRONMENT_HPP

#include "../Share/Config.hpp"
#include "SymbolItem.hpp"
#include "CompilingTimePackageStructure.hpp"

namespace XScript::Compiler {

    class CompilerEnvironment {
    public:
        CompilingTimePackageStructure MainPackage;

        XArray<std::pair<XString, CompilingTimePackageStructure>> DependencyPackages;

        XArray<std::pair<XString, SymbolItem>> Locals;

        XIndexType PushLocal(const XString &Name, const SymbolItem& Item);

        std::pair<XIndexType, SymbolItem> GetLocal(const XString &Name);
    };

} // Compiler

#endif //XSCRIPT2_COMPILERENVIRONMENT_HPP
