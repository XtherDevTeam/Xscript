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
        XString ClassName;

        XArray<XIndexType> ParentClasses;

        /**
         * Only record method names.
         * Records full method name, like ClassName$MethodName
         */
        XArray<XString> Methods;

        explicit CompilingTimeClass(const XString &Name,
                                    const XArray<XIndexType> &parentClasses,
                                    XArray<XString> methods);

        void PushMethod(const XString &Name);

        XIndexType IsMethodExist(const XString &Name);
    };

} // Compiler

#endif //XSCRIPT2_COMPILINGTIMECLASS_HPP
