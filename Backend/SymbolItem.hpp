//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_SYMBOLITEM_HPP
#define XSCRIPT2_SYMBOLITEM_HPP

#include "Typename.hpp"

namespace XScript {
    namespace Compiler {

        class SymbolItem {
        public:
            Typename ValueType;

            bool IsConstant;

            SymbolItem(const Typename &valueType, bool isConstant);
        };

    } // XScript
} // Compiler

#endif //XSCRIPT2_SYMBOLITEM_HPP
