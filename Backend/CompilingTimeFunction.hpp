//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_COMPILINGTIMEFUNCTION_HPP
#define XSCRIPT2_COMPILINGTIMEFUNCTION_HPP

#include "Typename.hpp"
#include "../Executor/BytecodeStructure.hpp"

namespace XScript::Compiler {

    class CompilingTimeFunction {
    public:
        enum class Descriptor : XInteger {
            Public,
            Private,
        };
        XArray<Descriptor> Descriptors;

        /**
         * 参数名称列表, 没有参数类型.
         */
        XArray<XString> ArgumentsList;

        /**
         * 字节码数组
         */
        XArray<BytecodeStructure> BytecodeArray;

        explicit CompilingTimeFunction(XArray<Descriptor> descriptors,
                                       const XArray<XString> &argumentsList);

        explicit CompilingTimeFunction(XArray<Descriptor> descriptors, const XArray<XString> &argumentsList,
                                       const XArray<BytecodeStructure> &bytecodeArray);
    };

} // Compiler

#endif //XSCRIPT2_COMPILINGTIMEFUNCTION_HPP
