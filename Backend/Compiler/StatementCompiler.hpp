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

            XArray<BytecodeStructure> Generate(AST &Target);

            XArray<BytecodeStructure> GenerateForVariableDeclaration(AST &Target);

            XArray<BytecodeStructure> GenerateForVariableDefinition(AST &Target);

            XArray<BytecodeStructure> GenerateForMemberDefineStatement(AST &Target);

            XArray<BytecodeStructure> GenerateForIfStatement(AST &Target);

            XArray<BytecodeStructure> GenerateForIfElseStatement(AST &Target);

            XArray<BytecodeStructure> GenerateForWhileStatement(AST &Target);

            XArray<BytecodeStructure> GenerateForForStatement(AST &Target);

            XArray<BytecodeStructure> GenerateForCodeBlock(AST &Target);

            static XArray<BytecodeStructure> GenerateForBreakStatement(AST &Target);

            static XArray<BytecodeStructure> GenerateForContinueStatement(AST &Target);

            XArray<BytecodeStructure> GenerateForReturnStatement(AST &Target);

            XArray <BytecodeStructure> GenerateForTryCatchStatement(AST &Target);

            XArray <BytecodeStructure> GenerateForThrowStatement(AST &Target);
        };

    } // XScript
} // Compiler

#endif //XSCRIPT2_STATEMENTCOMPILER_HPP
