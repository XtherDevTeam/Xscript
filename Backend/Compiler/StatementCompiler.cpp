//
// Created by Jerry Chou on 2022/5/24.
//

#include "StatementCompiler.hpp"
#include "../../Share/Exceptions/InternalException.hpp"
#include "ExpressionCompiler.hpp"

namespace XScript {
    namespace Compiler {
        StatementCompiler::StatementCompiler(CompilerEnvironment &environment) : BaseCompiler(environment) {

        }

        XArray<BytecodeStructure> StatementCompiler::Generate(AST &Target) {
            switch (Target.Type) {
                case AST::TreeType::VariableDeclaration: {
                    return GenerateForVariableDeclaration(Target);
                }
                case AST::TreeType::VariableDefinition: {
                    return GenerateForVariableDefinition(Target);
                }
                default: {
                    throw InternalException(L"StatementCompiler::Generate : Invalid invoke");
                }
            }
        }

        XArray<BytecodeStructure> StatementCompiler::GenerateForVariableDeclaration(AST &Target) {
            XArray<BytecodeStructure> Result;
            /* add to local frame */
            /* Typename就tm就是个摆设, 没用. */
            Environment.PushLocal(Target.Subtrees[0].Node.Value,
                                  (SymbolItem) {(Typename) {Typename::TypenameKind::Unknown}, false});

            Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::stack_push_empty,
                                                  (BytecodeStructure::InstructionParam) {(XHeapIndexType) {0}}});
            return Result;
        }

        XArray<BytecodeStructure> StatementCompiler::GenerateForVariableDefinition(AST &Target) {
            XArray<BytecodeStructure> Result;

            /* add to local frame */
            /* Typename就tm就是个摆设, 没用. */
            Environment.PushLocal(Target.Subtrees[0].Node.Value,
                                  (SymbolItem) {(Typename) {Typename::TypenameKind::Unknown}, false});

            MergeArray(Result, ExpressionCompiler(Environment).Generate(Target.Subtrees[1]));

            return Result;
        }
    } // XScript
} // Compiler