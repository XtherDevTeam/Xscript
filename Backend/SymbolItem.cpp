//
// Created by Jerry Chou on 2022/5/21.
//

#include "SymbolItem.hpp"

namespace XScript {
    namespace Compiler {
        SymbolItem::SymbolItem(const Typename &valueType, bool isConstant)
                : ValueType(valueType), IsConstant(isConstant) {}
    } // XScript
} // Compiler