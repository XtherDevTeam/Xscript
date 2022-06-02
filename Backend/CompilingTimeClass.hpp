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
        explicit CompilingTimeClass(const XArray<XIndexType> &parentClasses,
                                    XArray<XString> methods);

    public:

        XArray<XIndexType> ParentClasses;

        /**
         * Only record method names.
         * Records full method name, like ClassName$MethodName
         */
        XArray<XString> Methods;

        void PushMethod(const XString &Name);

        bool IsMethodExist(const XString &Name);
    };

} // Compiler

#endif //XSCRIPT2_COMPILINGTIMECLASS_HPP
