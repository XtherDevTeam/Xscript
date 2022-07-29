//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_COMPILINGTIMEPACKAGESTRUCTURE_HPP
#define XSCRIPT2_COMPILINGTIMEPACKAGESTRUCTURE_HPP

#include "../Share/Utils.hpp"
#include "CompilingTimeFunction.hpp"
#include "CompilingTimeClass.hpp"
#include "ConstantPool.hpp"

namespace XScript::Compiler {

    class CompilingTimePackageStructure {
    public:
        ConstantPool Constants;

        XArray<std::pair<XString, CompilingTimeFunction>> Functions;

        XArray<std::pair<XString, CompilingTimeClass>> Classes;

        XArray<std::pair<XString, SymbolItem>> Statics;

        XArray<BytecodeStructure> PackageInitializeCodes;

        XIndexType UnnamedFunctionCount{};

        XIndexType PushFunction(const XString &FunctionName, const CompilingTimeFunction &Function);

        XIndexType PushUnnamedFunction(const CompilingTimeFunction &Function);

        XIndexType PushClass(const XString &Name, const CompilingTimeClass &Item);

        XIndexType PushStatic(const XString &Name, const SymbolItem &Item);

        std::pair<XIndexType, CompilingTimeFunction &> GetFunction(const XString &Name);

        std::pair<XIndexType, CompilingTimeClass &> GetClass(const XString &Name);

        std::pair<XIndexType, SymbolItem &> GetStatic(const XString &Name);

        void AddMethodToClass(XIndexType ClassIndex, const XString &MethodName, const CompilingTimeFunction &Func);
    };

} // Compiler

#endif //XSCRIPT2_COMPILINGTIMEPACKAGESTRUCTURE_HPP
