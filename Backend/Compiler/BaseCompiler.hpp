//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_BASECOMPILER_HPP
#define XSCRIPT2_BASECOMPILER_HPP

#include "../../Share/Utils.hpp"
#include "../CompilerEnvironment.hpp"
#include "../../Frontend/AST.hpp"

namespace XScript::Compiler {

    class BaseCompiler {
    public:
        CompilerEnvironment &Environment;

        BaseCompiler() = delete;

        explicit BaseCompiler(CompilerEnvironment &environment);

        virtual XArray<BytecodeStructure> Generate(AST& Target) = 0;
    };

} // Compiler

#endif //XSCRIPT2_BASECOMPILER_HPP
