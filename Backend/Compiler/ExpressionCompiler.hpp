//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_EXPRESSIONCOMPILER_HPP
#define XSCRIPT2_EXPRESSIONCOMPILER_HPP

#include "BaseCompiler.hpp"

namespace XScript::Compiler {

    class ExpressionCompiler : BaseCompiler {
    public:
        explicit ExpressionCompiler(CompilerEnvironment &Environment);

        XArray<BytecodeStructure> ParseMemberExpression(AST &Target, bool IsMemberExpression);

        XArray<BytecodeStructure> ParseClassMethodInvoke(AST &Target, CompilingTimeClass *&IsInParsing);

        XArray<BytecodeStructure> ParseMemberExpressionEndWithAssignment(AST &Target, bool IsMemberExpression);

        XArray<BytecodeStructure> ParseNewExpression(AST &Target);

        XArray<BytecodeStructure> Generate(AST &Target) override;
    };

} // Compiler

#endif //XSCRIPT2_EXPRESSIONCOMPILER_HPP
