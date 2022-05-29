//
// Created by Jerry Chou on 2022/5/29.
//

#include "FileCompiler.hpp"
#include "StatementCompiler.hpp"

namespace XScript {
    namespace Compiler {
        FileCompiler::FileCompiler(CompilerEnvironment &Environment) : BaseCompiler(Environment) {

        }

        XArray<BytecodeStructure> FileCompiler::Generate(AST &Target) {
            switch (Target.Type) {
                case AST::TreeType::FunctionDefinition:
                    return GenerateForFunctionDefinition(Target);
                case AST::TreeType::VariableDeclaration:
                    return GenerateForVariableDeclaration(Target);
                case AST::TreeType::VariableDefinition:
                    return GenerateForVariableDefinition(Target);
            }
        }

        XArray<BytecodeStructure> FileCompiler::GenerateForFunctionDefinition(AST &Target) {
            XArray<XString> Params;

            XArray<BytecodeStructure> Structure;

            /**
             * initialize params
             */
            for (auto &I: Target.Subtrees[1].Subtrees) {
                Params.push_back(I.Node.Value);
            }

            Structure = StatementCompiler(Environment).GenerateForCodeBlock(Target.Subtrees[2]);

            CompilingTimeFunction Func{
                    XArray<CompilingTimeFunction::Descriptor>{CompilingTimeFunction::Descriptor::Public}, Params,
                    Structure};

            Environment.MainPackage.PushFunction(Target.Subtrees[0].Node.Value, Func);
            return {};
        }

        XArray<BytecodeStructure> FileCompiler::GenerateForVariableDeclaration(AST &Target) {
            /* TODO: Add command static_store */
            return {};
        }

        XArray<BytecodeStructure> FileCompiler::GenerateForVariableDefinition(AST &Target) {
            /* TODO: Add package statics initializer */
            return {};
        }
    } // XScript
} // Compiler