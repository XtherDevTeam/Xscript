//
// Created by Jerry Chou on 2022/5/29.
//

#ifndef XSCRIPT2_FILECOMPILER_HPP
#define XSCRIPT2_FILECOMPILER_HPP

#include "BaseCompiler.hpp"

namespace XScript {
    namespace Compiler {

        class FileCompiler : BaseCompiler {
        public:
            explicit FileCompiler(CompilerEnvironment &Environment);

            XArray<BytecodeStructure> Generate(XScript::AST &Target) override;

            XArray<BytecodeStructure> GenerateForFunctionDefinition(AST &Target);

            XArray<BytecodeStructure> GenerateForVariableDeclaration(AST &Target);

            XArray<BytecodeStructure> GenerateForVariableDefinition(AST &Target);

            XArray<BytecodeStructure> GenerateForFile(AST &Target);
        };

    } // XScript
} // Compiler

#endif //XSCRIPT2_FILECOMPILER_HPP
