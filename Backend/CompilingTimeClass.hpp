//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_COMPILINGTIMECLASS_HPP
#define XSCRIPT2_COMPILINGTIMECLASS_HPP

#include <utility>
#include "../Share/Utils.hpp"
#include "CompilingTimeFunction.hpp"
#include "SymbolItem.hpp"
#include "ClassDescriptor.hpp"

namespace XScript::Compiler {

    class CompilingTimeClass {
    public:
        XString ClassName;

        XArray<ClassDescriptor> ParentClasses;

        /**
         * Only record method names.
         * Records full method name, like ClassName$MethodName
         */
        XArray<XString> Methods;

        explicit CompilingTimeClass(const XString &Name,
                                    const XArray <ClassDescriptor> &parentClasses,
                                    XArray<XString> methods);

        void PushMethod(const XString &Name);

        XIndexType IsMethodExist(const XString &Name);
    };

} // Compiler

#endif //XSCRIPT2_COMPILINGTIMECLASS_HPP
