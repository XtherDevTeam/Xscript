//
// Created by Jerry Chou on 2022/5/21.
//

#include "CompilingTimePackageStructure.hpp"
#include "../Share/XScriptException.hpp"
#include "../Share/Exceptions/InternalException.hpp"

namespace XScript {
    namespace Compiler {
        XIndexType CompilingTimePackageStructure::PushFunction(const XString &FunctionName,
                                                               const CompilingTimeFunction &Function) {
            Functions.push_back(std::make_pair(FunctionName, Function));
            return Functions.size() - 1;
        }

        XIndexType
        CompilingTimePackageStructure::PushClass(const XString &Name, const CompilingTimeClass &Item) {
            Classes.push_back(std::make_pair(Name, Item));
            return Classes.size() - 1;
        }

        XIndexType CompilingTimePackageStructure::PushStatic(const XString &Name, const SymbolItem &Item) {
            Statics.push_back(std::make_pair(Name, Item));
            return Statics.size() - 1;
        }

        CompilingTimeFunction &CompilingTimePackageStructure::GetFunction(const XString &Name) {
            for (auto &Index : Functions) {
                if (Index.first == Name) return Index.second;
            }
            throw XScript::InternalException(L"Cannot find a function named " + Name + L" in package");
        }

        CompilingTimeClass &CompilingTimePackageStructure::GetClass(const XString &Name) {
            for (auto &Index : Classes) {
                if (Index.first == Name) return Index.second;
            }
            throw XScript::InternalException(L"Cannot find a class named " + Name + L" in package");
        }

        SymbolItem &CompilingTimePackageStructure::GetStatic(const XString &Name) {
            for (auto &Index : Statics) {
                if (Index.first == Name) return Index.second;
            }
            throw XScript::InternalException(L"Cannot find a static member named " + Name + L" in package");
        }
    } // XScript
} // Compiler