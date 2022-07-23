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
                case AST::TreeType::NewExpression:
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
                case AST::TreeType::TypeCastingExpression: {
                    auto Result = ExpressionCompiler(Environment).Generate(Target);
                    Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::stack_pop,
                                                          (BytecodeStructure::InstructionParam) {(XHeapIndexType) 0}});
                    return Result;
                }
                case AST::TreeType::AssignmentExpression: {
                    auto Result = ExpressionCompiler(Environment).Generate(Target);
                    return Result;
                }

                case AST::TreeType::VariableDeclaration: {
                    return GenerateForVariableDeclaration(Target);
                }
                case AST::TreeType::VariableDefinition: {
                    return GenerateForVariableDefinition(Target);
                }
                case AST::TreeType::MemberDefineStatement: {
                    return GenerateForMemberDefineStatement(Target);
                }
                case AST::TreeType::IfStatement: {
                    return GenerateForIfStatement(Target);
                }
                case AST::TreeType::IfElseStatement: {
                    return GenerateForIfElseStatement(Target);
                }
                case AST::TreeType::ThrowStatement: {
                    return GenerateForThrowStatement(Target);
                }
                case AST::TreeType::TryCatchStatement: {
                    return GenerateForTryCatchStatement(Target);
                }
                case AST::TreeType::WhileStatement: {
                    return GenerateForWhileStatement(Target);
                }
                case AST::TreeType::ForStatement: {
                    return GenerateForForStatement(Target);
                }
                case AST::TreeType::CodeBlockStatement: {
                    return GenerateForCodeBlock(Target);
                }
                case AST::TreeType::BreakStatement: {
                    return GenerateForBreakStatement(Target);
                }
                case AST::TreeType::ContinueStatement: {
                    return GenerateForContinueStatement(Target);
                }
                case AST::TreeType::ReturnStatement: {
                    return GenerateForReturnStatement(Target);
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
                                                          (XInteger) {static_cast<XInteger>(CodeBlock.size() + 1)}}});

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
                                                          (XInteger) {static_cast<XInteger>(CodeBlock.size() + 1)}}});

            MergeArray(Result, CodeBlock);

            MergeArray(Result, ElseBlock);

            return Result;
        }

        XArray<BytecodeStructure> StatementCompiler::GenerateForCodeBlock(AST &Target) {
            XIndexType NowLocals = Environment.Locals.size();

            XArray<BytecodeStructure> Result;

            for (auto &Subtree: Target.Subtrees) {
                MergeArray(Result, Generate(Subtree));
            }

            /**
             * Restore local symbol index
             */
            for (XIndexType I = 0; I < Environment.Locals.size() - NowLocals; I++) {
                Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::stack_pop,
                                                      (BytecodeStructure::InstructionParam) {(XHeapIndexType) 0}});
                Environment.Locals.pop_back();
            }

            return Result;
        }

        XArray<BytecodeStructure> StatementCompiler::GenerateForWhileStatement(AST &Target) {
            XArray<BytecodeStructure> Result, Condition, CodeBlock;

            MergeArray(Condition, ExpressionCompiler(Environment).Generate(Target.Subtrees[0]));

            MergeArray(CodeBlock, GenerateForCodeBlock(Target.Subtrees[1]));

            /**
             * Preprocessing for code block
             */
            for (XIndexType I = 0; I < CodeBlock.size(); I++) {
                auto &Command = CodeBlock[I];

                if (Command.Instruction == BytecodeStructure::InstructionEnum::fake_command_break) {
                    Command.Instruction = BytecodeStructure::InstructionEnum::pc_jump;
                    Command.Param = (BytecodeStructure::InstructionParam) {
                            static_cast<XInteger>(CodeBlock.size() - I + 1)};
                } else if (Command.Instruction == BytecodeStructure::InstructionEnum::fake_command_continue) {
                    Command.Instruction = BytecodeStructure::InstructionEnum::pc_jump;
                    Command.Param = (BytecodeStructure::InstructionParam) {
                            static_cast<XInteger>(CodeBlock.size() - I)};
                }
            }

            Condition.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::pc_jump_if_false,
                                                     (BytecodeStructure::InstructionParam) {
                                                             (XInteger) {
                                                                     static_cast<XInteger>(CodeBlock.size() + 2)}}});

            MergeArray(Result, Condition);
            /* 为跳回命令reserve一个命令单位 */

            MergeArray(Result, CodeBlock);
            /* jump back to the condition block */
            Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::pc_jump,
                                                  (BytecodeStructure::InstructionParam) {
                                                          (XInteger) {static_cast<XInteger>(-(CodeBlock.size() +
                                                                                              Condition.size()))}}});

            return Result;
        }

        XArray<BytecodeStructure> StatementCompiler::GenerateForForStatement(AST &Target) {
            XIndexType NowLocals = Environment.Locals.size();

            XArray<BytecodeStructure> Result, InitialStatement, Condition, AfterStatement, CodeBlock;

            InitialStatement = Generate(Target.Subtrees[0]);
            Condition = ExpressionCompiler(Environment).Generate(Target.Subtrees[1]);
            AfterStatement = Generate(Target.Subtrees[2]);
            CodeBlock = GenerateForCodeBlock(Target.Subtrees[3]);

            /**
             * Preprocessing for code block
             */
            for (XIndexType I = 0; I < CodeBlock.size(); I++) {
                auto &Command = CodeBlock[I];

                if (Command.Instruction == BytecodeStructure::InstructionEnum::fake_command_break) {
                    Command.Instruction = BytecodeStructure::InstructionEnum::pc_jump;
                    Command.Param = (BytecodeStructure::InstructionParam) {
                            static_cast<XInteger>(CodeBlock.size() - I + AfterStatement.size() + 1)};
                } else if (Command.Instruction == BytecodeStructure::InstructionEnum::fake_command_continue) {
                    Command.Instruction = BytecodeStructure::InstructionEnum::pc_jump;
                    Command.Param = (BytecodeStructure::InstructionParam) {
                            static_cast<XInteger>(CodeBlock.size() - I)};
                }
            }

            MergeArray(Result, InitialStatement);

            /**
             * reserve one command for jump-back command
             */
            Condition.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::pc_jump_if_false,
                                                     (BytecodeStructure::InstructionParam) {
                                                             (XInteger) {static_cast<XInteger>(CodeBlock.size() +
                                                                                               AfterStatement.size() +
                                                                                               2)}}});

            MergeArray(Result, Condition);

            MergeArray(Result, CodeBlock);
            MergeArray(Result, AfterStatement);

            /* jump back to the condition block */
            Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::pc_jump,
                                                  (BytecodeStructure::InstructionParam) {
                                                          (XInteger) {static_cast<XInteger>(-(AfterStatement.size() +
                                                                                              CodeBlock.size() +
                                                                                              Condition.size()))}}});

            /**
             * Restore local symbol index
             */
            for (XIndexType I = 0; I < Environment.Locals.size() - NowLocals; I++) {
                Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::stack_pop,
                                                      (BytecodeStructure::InstructionParam) {(XHeapIndexType) 0}});
                Environment.Locals.pop_back();
            }

            return Result;
        }

        XArray<BytecodeStructure> StatementCompiler::GenerateForBreakStatement(AST &Target) {
            XArray<BytecodeStructure> Result;
            Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::fake_command_break,
                                                  (BytecodeStructure::InstructionParam) {(XHeapIndexType) 0}});
            return Result;
        }

        XArray<BytecodeStructure> StatementCompiler::GenerateForContinueStatement(XScript::AST &Target) {
            XArray<BytecodeStructure> Result;
            Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::fake_command_continue,
                                                  (BytecodeStructure::InstructionParam) {(XHeapIndexType) 0}});
            return Result;
        }

        XArray<BytecodeStructure> StatementCompiler::GenerateForReturnStatement(AST &Target) {
            XArray<BytecodeStructure> Result;
            MergeArray(Result, ExpressionCompiler(Environment).Generate(Target.Subtrees[0]));
            Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::func_return,
                                                  (BytecodeStructure::InstructionParam) {(XHeapIndexType) 0}});
            return Result;
        }

        XArray<BytecodeStructure> StatementCompiler::GenerateForMemberDefineStatement(AST &Target) {
            XArray<BytecodeStructure> Result;
            MergeArray(Result, ExpressionCompiler(Environment).ParseMemberExpression(Target.Subtrees[1], false));
            Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::class_new_member,
                                                  (BytecodeStructure::InstructionParam) {
                                                          (XHeapIndexType) Hash(Target.Subtrees[0].Node.Value)}});
            return Result;
        }

        XArray<BytecodeStructure> StatementCompiler::GenerateForTryCatchStatement(AST &Target) {
            XArray<BytecodeStructure> Result, TryBlock, CatchBlock, FinallyBlock;
            MergeArray(TryBlock, GenerateForCodeBlock(Target.Subtrees[0]));
            TryBlock.push_back((BytecodeStructure) {
                    BytecodeStructure::InstructionEnum::exception_pop,
                    (BytecodeStructure::InstructionParam) {(XHeapIndexType) {}}
            });
            Result.push_back((BytecodeStructure) {
                    BytecodeStructure::InstructionEnum::exception_push,
                    (BytecodeStructure::InstructionParam) {static_cast<XInteger>(TryBlock.size() + 1)}
            });

            Environment.PushLocal(Target.Subtrees[1].Node.Value,
                                  (SymbolItem) {(Typename) {Typename::TypenameKind::Unknown}, false});
            MergeArray(CatchBlock, GenerateForCodeBlock(Target.Subtrees[2]));
            CatchBlock.push_back((BytecodeStructure) {
                    BytecodeStructure::InstructionEnum::stack_pop,
                    (BytecodeStructure::InstructionParam) {(XHeapIndexType) {}}
            });
            Environment.Locals.pop_back();
            MergeArray(FinallyBlock, GenerateForCodeBlock(Target.Subtrees[3]));
            TryBlock.push_back((BytecodeStructure) {
                    BytecodeStructure::InstructionEnum::pc_jump,
                    (BytecodeStructure::InstructionParam) {static_cast<XInteger>(CatchBlock.size() + 1)}
            });
            MergeArray(Result, TryBlock);
            MergeArray(Result, CatchBlock);
            MergeArray(Result, FinallyBlock);
            return Result;
        }

        XArray<BytecodeStructure> StatementCompiler::GenerateForThrowStatement(AST &Target) {
            XArray<BytecodeStructure> Result;
            MergeArray(Result, ExpressionCompiler(Environment).Generate(Target.Subtrees[0]));
            Result.push_back((BytecodeStructure) {
                    BytecodeStructure::InstructionEnum::exception_throw,
                    (BytecodeStructure::InstructionParam) {(XIndexType) {}}
            });
            return Result;
        }
    } // XScript
} // Compiler