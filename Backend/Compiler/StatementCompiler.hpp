//
// Created by Jerry Chou on 2022/5/24.
//

#ifndef XSCRIPT2_STATEMENTCOMPILER_HPP
#define XSCRIPT2_STATEMENTCOMPILER_HPP

#include "BaseCompiler.hpp"

namespace XScript {
    namespace Compiler {

        class StatementCompiler : BaseCompiler {
        public:
            explicit StatementCompiler(CompilerEnvironment &environment);

            XArray<BytecodeStructure> Generate(AST& Target);

            XArray<BytecodeStructure> GenerateForVariableDeclaration(AST &Target);

            XArray<BytecodeStructure> GenerateForVariableDefinition(AST &Target);

            XArray<BytecodeStructure> GenerateForIfStatement(AST &Target);

            XArray<BytecodeStructure> GenerateForIfElseStatement(AST &Target);

            XArray<BytecodeStructure> GenerateForWhileStatement(AST &Target);

            XArray<BytecodeStructure> GenerateForCodeBlock(AST &Target);
        };

    } // XScript
} // Compiler

#endif //XSCRIPT2_STATEMENTCOMPILER_HPP
