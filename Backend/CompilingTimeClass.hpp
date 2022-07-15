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

        // alias(invoke name), real name
        XArray<std::pair<XString, XString>> Methods;

        explicit CompilingTimeClass(const XString &ClassName, const XArray<ClassDescriptor> &parentClasses,
                                    XArray<std::pair<XString, XString>> methods);

        void PushMethod(const XString &Name, const XString &RealName);

        XIndexType IsMethodExist(const XString &Name);
    };

} // Compiler

#endif //XSCRIPT2_COMPILINGTIMECLASS_HPP
