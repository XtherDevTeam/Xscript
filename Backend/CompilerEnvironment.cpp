//
// Created by Jerry Chou on 2022/5/21.
//

#include "CompilerEnvironment.hpp"
#include "../Share/Exceptions/InternalException.hpp"

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
} // Compiler