//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_COMPILINGTIMECLASS_HPP
#define XSCRIPT2_COMPILINGTIMECLASS_HPP

#include <utility>
#include "../Share/Utils.hpp"
#include "CompilingTimeFunction.hpp"
#include "SymbolItem.hpp"

namespace XScript::Compiler {

    class CompilingTimeClass {
    public:
        explicit CompilingTimeClass(const XArray <XIndexType> &parentClasses,
                                    XArray <std::pair<XString, CompilingTimeFunction>> methods,
                                    XArray <std::pair<XString, SymbolItem>> members);

    public:
        XArray<XIndexType> ParentClasses;

        XArray<std::pair<XString, CompilingTimeFunction>> Methods;

        XArray<std::pair<XString, SymbolItem>> Members;
    };

} // Compiler

#endif //XSCRIPT2_COMPILINGTIMECLASS_HPP
