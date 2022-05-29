//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_COMPILINGTIMEPACKAGESTRUCTURE_HPP
#define XSCRIPT2_COMPILINGTIMEPACKAGESTRUCTURE_HPP

#include "../Share/Utils.hpp"
#include "CompilingTimeFunction.hpp"
#include "CompilingTimeClass.hpp"

namespace XScript::Compiler {

    class CompilingTimePackageStructure {
    public:
        XArray<std::pair<XString, CompilingTimeFunction>> Functions;

        XArray<std::pair<XString, CompilingTimeClass>> Classes;

        XArray<std::pair<XString, SymbolItem>> Statics;

        XArray<BytecodeStructure> PackageInitializeCodes;

        XIndexType PushFunction(const XString &FunctionName, const CompilingTimeFunction &Function);

        XIndexType PushClass(const XString &Name, const CompilingTimeClass &Item);

        XIndexType PushStatic(const XString &Name, const SymbolItem &Item);

        std::pair<XIndexType, CompilingTimeFunction &> GetFunction(const XString &Name);

        std::pair<XIndexType, CompilingTimeClass &> GetClass(const XString &Name);

        std::pair<XIndexType, SymbolItem &> GetStatic(const XString &Name);
    };

} // Compiler

#endif //XSCRIPT2_COMPILINGTIMEPACKAGESTRUCTURE_HPP
