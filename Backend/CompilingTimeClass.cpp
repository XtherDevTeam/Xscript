//
// Created by Jerry Chou on 2022/5/21.
//

#include "CompilingTimeClass.hpp"

namespace XScript {
    namespace Compiler {
        CompilingTimeClass::CompilingTimeClass(const XArray <XIndexType> &parentClasses,
                                               XArray <std::pair<XString, CompilingTimeFunction>> methods,
                                               XArray <std::pair<XString, SymbolItem>> members)
                : ParentClasses(
                parentClasses), Methods(methods), Members(members) {}
    } // XScript
} // Compiler