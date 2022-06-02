//
// Created by Jerry Chou on 2022/5/29.
//

#include "FileCompiler.hpp"
#include "StatementCompiler.hpp"
#include "ExpressionCompiler.hpp"
#include "../../Share/Exceptions/InternalException.hpp"

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
                default:
                    throw InternalException(L"FileCompiler::Generate : Invalid invoke");
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
            Environment.MainPackage.PushStatic(Target.Subtrees[0].Node.Value,
                                               (SymbolItem) {(Typename) {Typename::TypenameKind::Unknown}, false});
            return {};
        }

        XArray<BytecodeStructure> FileCompiler::GenerateForVariableDefinition(AST &Target) {
            auto Index = Environment.MainPackage.PushStatic(Target.Subtrees[0].Node.Value,
                                                            (SymbolItem) {(Typename) {Typename::TypenameKind::Unknown},
                                                                          false});

            MergeArray(Environment.MainPackage.PackageInitializeCodes,
                       ExpressionCompiler(Environment).Generate(Target.Subtrees[1]));
            Environment.MainPackage.PackageInitializeCodes.push_back(
                    (BytecodeStructure) {BytecodeStructure::InstructionEnum::static_store,
                                         (BytecodeStructure::InstructionParam) {Index}}
            );
            return {};
        }

        XArray<BytecodeStructure> FileCompiler::GenerateForFile(AST &Target) {
            XArray<BytecodeStructure> Result;
            for (auto &Subtree: Target.Subtrees) {
                MergeArray(Result, Generate(Subtree));
            }
            return Result;
        }
    } // XScript
} // Compiler