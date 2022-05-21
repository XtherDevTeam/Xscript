//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_EXPRESSIONCOMPILER_HPP
#define XSCRIPT2_EXPRESSIONCOMPILER_HPP

#include "BaseCompiler.hpp"

namespace XScript::Compiler {

    class ExpressionCompiler : BaseCompiler {
        explicit ExpressionCompiler(CompilerEnvironment& Environment);

        XArray<BytecodeStructure> ParseMemberExpression(AST &Target, XIndexType &ClassIndex);

        XArray<BytecodeStructure> Generate(AST& Target) override;
    };

} // Compiler

#endif //XSCRIPT2_EXPRESSIONCOMPILER_HPP
