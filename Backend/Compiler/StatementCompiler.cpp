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
                case AST::TreeType::Primary:
                case AST::TreeType::Identifier:
                case AST::TreeType::IndexExpression:
                case AST::TreeType::MemberExpression:
                case AST::TreeType::IncrementExpression:
                case AST::TreeType::DecrementExpression:
                case AST::TreeType::MultiplicationExpression:
                case AST::TreeType::AdditionExpression:
                case AST::TreeType::EqualExpression:
                case AST::TreeType::LogicExpression:
                case AST::TreeType::BinaryExpression:
                case AST::TreeType::BinaryMoveExpression:
                case AST::TreeType::ComparingExpression:
                case AST::TreeType::FunctionCallingExpression:
                case AST::TreeType::NegativeExpression:
                case AST::TreeType::TypeCastingExpression:
                case AST::TreeType::AssignmentExpression:
                    return ExpressionCompiler(Environment).Generate(Target);

                case AST::TreeType::VariableDeclaration: {
                    return GenerateForVariableDeclaration(Target);
                }
                case AST::TreeType::VariableDefinition: {
                    return GenerateForVariableDefinition(Target);
                }
                case AST::TreeType::IfStatement: {
                    return GenerateForIfStatement(Target);
                }
                case AST::TreeType::IfElseStatement: {
                    return GenerateForIfElseStatement(Target);
                }
                case AST::TreeType::WhileStatement: {
                    return GenerateForWhileStatement(Target);
                }
                case AST::TreeType::CodeBlockStatement: {
                    return GenerateForCodeBlock(Target);
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

        XArray<BytecodeStructure> StatementCompiler::GenerateForIfStatement(AST &Target) {
            XArray<BytecodeStructure> Result, CodeBlock;
            MergeArray(Result, ExpressionCompiler(Environment).Generate(Target.Subtrees[0]));

            MergeArray(CodeBlock, GenerateForCodeBlock(Target.Subtrees[1]));

            // 如果条件不满足，则跳转到代码块的后面
            Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::pc_jump_if_false,
                                                  (BytecodeStructure::InstructionParam) {
                                                          (XInteger) CodeBlock.size() + 1}});

            MergeArray(Result, CodeBlock);

            return Result;
        }

        XArray<BytecodeStructure> StatementCompiler::GenerateForIfElseStatement(AST &Target) {
            XArray<BytecodeStructure> Result, CodeBlock, ElseBlock;
            MergeArray(Result, ExpressionCompiler(Environment).Generate(Target.Subtrees[0]));

            MergeArray(CodeBlock, GenerateForCodeBlock(Target.Subtrees[1]));

            MergeArray(ElseBlock, Generate(Target.Subtrees[2]));

            // 如果条件不满足，则跳转到ElseBlock
            Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::pc_jump_if_false,
                                                  (BytecodeStructure::InstructionParam) {
                                                          (XInteger) CodeBlock.size() + 1}});

            MergeArray(Result, CodeBlock);

            MergeArray(Result, ElseBlock);

            return Result;
        }

        XArray<BytecodeStructure> StatementCompiler::GenerateForCodeBlock(AST &Target) {
            XArray<BytecodeStructure> Result;
            Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::stack_push_frame,
                                                  (BytecodeStructure::InstructionParam) {(XHeapIndexType) 0}});

            for (auto &Subtree: Target.Subtrees) {
                MergeArray(Result, Generate(Subtree));
            }

            Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::stack_pop_frame,
                                                  (BytecodeStructure::InstructionParam) {(XHeapIndexType) 0}});
            return Result;
        }

        XArray<BytecodeStructure> StatementCompiler::GenerateForWhileStatement(AST &Target) {
            XArray<BytecodeStructure> Result, Condition, CodeBlock;

            MergeArray(Condition, ExpressionCompiler(Environment).Generate(Target.Subtrees[0]));

            MergeArray(CodeBlock, GenerateForCodeBlock(Target.Subtrees[1]));

            Condition.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::pc_jump_if_false,
                                                     (BytecodeStructure::InstructionParam) {
                                                             (XInteger) CodeBlock.size() + 2}});

            MergeArray(Result, Condition);
            /* 为跳回命令reserve一个命令单位 */

            MergeArray(Result, CodeBlock);
            /* jump back to the condition block */
            Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::pc_jump,
                                                  (BytecodeStructure::InstructionParam) {
                                                          (XInteger) -(CodeBlock.size() + Condition.size())}});

            return Result;
        }
    } // XScript
} // Compiler