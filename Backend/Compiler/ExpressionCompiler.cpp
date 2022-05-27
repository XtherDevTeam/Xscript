//
// Created by Jerry Chou on 2022/5/21.
//

#include "ExpressionCompiler.hpp"
#include "../../Share/Exceptions/InternalException.hpp"
#include "../../Share/Exceptions/CompilerError.hpp"

namespace XScript::Compiler {
    ExpressionCompiler::ExpressionCompiler(CompilerEnvironment &Environment) : BaseCompiler(Environment) {

    }

    XArray<BytecodeStructure> ExpressionCompiler::Generate(AST &Target) {
        XArray<BytecodeStructure> Result;
        switch (Target.Type) {
            /* get variable lvalue and covert to rvalue */
            case AST::TreeType::Identifier:
            case AST::TreeType::IndexExpression:
            case AST::TreeType::FunctionCallingExpression:
            case AST::TreeType::MemberExpression: {
                MergeArray(Result, ParseMemberExpression(Target, false));
                break;
            }

            case AST::TreeType::Primary: {
                switch (Target.Node.Kind) {
                    case Lexer::TokenKind::String:
                        /* TODO: Add constant pool to XScript 2 */
                        break;
                    case Lexer::TokenKind::Integer:
                        Result.push_back(
                                (BytecodeStructure) {BytecodeStructure::InstructionEnum::stack_push_integer,
                                                     (BytecodeStructure::InstructionParam) {
                                                             (XInteger) XStringToXInteger(Target.Node.Value)}});
                        break;
                    case Lexer::TokenKind::Decimal:
                        Result.push_back(
                                (BytecodeStructure) {BytecodeStructure::InstructionEnum::stack_push_decimal,
                                                     (BytecodeStructure::InstructionParam) {
                                                             (XDecimal) XStringToXDecimal(Target.Node.Value)}});
                        break;
                    case Lexer::TokenKind::Boolean:
                        Result.push_back(
                                (BytecodeStructure) {BytecodeStructure::InstructionEnum::stack_push_boolean,
                                                     (BytecodeStructure::InstructionParam) {
                                                             (XBoolean) {Target.Node.Value == L"True"}}});
                        break;
                    default:
                        throw InternalException(L"Unexpected AST Type");
                }
                break;
            }

            case AST::TreeType::NegativeExpression: {
                MergeArray(Result, Generate(Target.Subtrees.back()));
                Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::calculation_negate,
                                                      (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                break;
            }
            case AST::TreeType::IncrementExpression: {
                MergeArray(Result, ParseMemberExpression(Target.Subtrees.back(), false));
                Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::calculation_increment,
                                                      (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                break;
            }
            case AST::TreeType::DecrementExpression: {
                MergeArray(Result, ParseMemberExpression(Target.Subtrees.back(), false));
                Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::calculation_decrement,
                                                      (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                break;
            }

            case AST::TreeType::AdditionExpression:
            case AST::TreeType::MultiplicationExpression:
            case AST::TreeType::BinaryMoveExpression: {
                /* It is pushed from left to right */
                MergeArray(Result, Generate(Target.Subtrees[0]));
                MergeArray(Result, Generate(Target.Subtrees[2]));

                /* Calculation will pop 2 values and push the result into stack automatically */
                switch (Target.Subtrees[1].Node.Kind) {
                    case Lexer::TokenKind::Asterisk: {
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::calculation_mul,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    }
                    case Lexer::TokenKind::Slash: {
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::calculation_div,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    }
                    case Lexer::TokenKind::PercentSign: {
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::calculation_mod,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    }
                    case Lexer::TokenKind::Plus: {
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::calculation_add,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    }
                    case Lexer::TokenKind::Minus: {
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::calculation_sub,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    }
                    case Lexer::TokenKind::BinaryLeftMove: {
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::binary_lm,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    }
                    case Lexer::TokenKind::BinaryRightMove: {
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::binary_rm,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    }
                    default: {
                        /* never run into here */
                        break;
                    }
                }
                break;
            }

            case AST::TreeType::LogicExpression:
            case AST::TreeType::EqualExpression:
            case AST::TreeType::ComparingExpression: {
                /* It is pushed from left to right */
                MergeArray(Result, Generate(Target.Subtrees[0]));
                MergeArray(Result, Generate(Target.Subtrees[2]));

                switch (Target.Subtrees[1].Node.Kind) {
                    case Lexer::TokenKind::MoreThan: {
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::logic_great,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    }
                    case Lexer::TokenKind::LessThan: {
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::logic_less,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    }
                    case Lexer::TokenKind::MoreThanOrEqual: {
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::logic_great_equal,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    }
                    case Lexer::TokenKind::LessThanOrEqual: {
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::logic_less_equal,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    }
                    case Lexer::TokenKind::Equal: {
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::logic_equal,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    }
                    case Lexer::TokenKind::NotEqual: {
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::logic_not_equal,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    }
                    case Lexer::TokenKind::LogicOr: {
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::logic_or,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    }
                    case Lexer::TokenKind::LogicAnd: {
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::logic_and,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    }
                    default: {
                        /* never run into here */
                        break;
                    }
                }
                break;
            }

            case AST::TreeType::BinaryExpression: {
                /* It is pushed from left to right */
                MergeArray(Result, Generate(Target.Subtrees[0]));
                MergeArray(Result, Generate(Target.Subtrees[2]));

                switch (Target.Subtrees[1].Node.Kind) {
                    case Lexer::TokenKind::BinaryXOR: {
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::binary_xor,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    }
                    case Lexer::TokenKind::BinaryOr: {
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::binary_or,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    }
                    case Lexer::TokenKind::BinaryAnd: {
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::binary_and,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    }
                    default:
                        /* never run into here */
                        break;
                }
                break;
            }

            case AST::TreeType::AssignmentExpression: {
                /* Push lvalue into stack */
                MergeArray(Result, Generate(Target.Subtrees[0]));
                MergeArray(Result, Generate(Target.Subtrees[2]));

                switch (Target.Subtrees[1].Node.Kind) {
                    case Lexer::TokenKind::AdditionAssignment:
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::calculation_add,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    case Lexer::TokenKind::SubtractionAssignment:
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::calculation_sub,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    case Lexer::TokenKind::MultiplicationAssignment:
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::calculation_mul,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    case Lexer::TokenKind::DivisionAssignment:
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::calculation_div,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    case Lexer::TokenKind::RemainderAssignment:
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::calculation_mod,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    default:
                        /* never run into here */
                        break;
                }

                MergeArray(Result, ParseMemberExpressionEndWithAssignment(Target.Subtrees[0], false));
                break;
            }

            default:
                throw XScript::CompilerError(Target.GetFirstNotNullToken().Line,
                                             Target.GetFirstNotNullToken().Column, L"Unexpected AST Type");
        }
        return Result;
    }

    XArray<BytecodeStructure> ExpressionCompiler::ParseMemberExpression(AST &Target, bool IsMemberExpression) {
        XArray<BytecodeStructure> Result;

        switch (Target.Type) {
            case AST::TreeType::Identifier: {
                if (IsMemberExpression) {
                    Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::class_get_member,
                                                          (BytecodeStructure::InstructionParam) {
                                                                  Hash(Target.Node.Value)}});
                } else {
                    try {
                        /* If variable doesn't exist, then GetLocal will throw an error */
                        auto Item = Environment.GetLocal(Target.Node.Value);
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::stack_duplicate,
                                                              (BytecodeStructure::InstructionParam) {Item.first}});
                    } catch (InternalException &E) {
                        try {
                            /* If variable doesn't exist, then GetStatic will throw an error */
                            auto Item = Environment.MainPackage.GetStatic(Target.Node.Value);
                            Result.push_back(
                                    (BytecodeStructure) {BytecodeStructure::InstructionEnum::stack_duplicate,
                                                         (BytecodeStructure::InstructionParam) {Item.first}});
                        } catch (InternalException &E) {
                            throw CompilerError(Target.Node.Line, Target.Node.Column, string2wstring(E.what()));
                        }
                    }
                }
                break;
            }
            case AST::TreeType::IndexExpression: {
                XArray<BytecodeStructure> Index = Generate(Target.Subtrees[1]);
                MergeArray(Result, Index);
                Result.push_back(
                        (BytecodeStructure) {BytecodeStructure::InstructionEnum::list_get_member,
                                             (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                break;
            }
            case AST::TreeType::FunctionCallingExpression: {
                /* TODO: Complete here. */
                break;
            }
            case AST::TreeType::MemberExpression: {
                MergeArray(Result, ParseMemberExpression(Target.Subtrees[0], IsMemberExpression));
                MergeArray(Result, ParseMemberExpression(Target.Subtrees[2], true));
                break;
            }

            default:
                throw CompilerError(Target.GetFirstNotNullToken().Line,
                                    Target.GetFirstNotNullToken().Column,
                                    L"ParserMemberExpression: Unexpected AST Type");
        }
        return Result;
    }

    XArray<BytecodeStructure>
    ExpressionCompiler::ParseMemberExpressionEndWithAssignment(AST &Target, bool IsMemberExpression) {
        XArray<BytecodeStructure> Result;

        switch (Target.Type) {
            case AST::TreeType::Identifier: {
                if (IsMemberExpression) {
                    Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::class_assign_member,
                                                          (BytecodeStructure::InstructionParam) {
                                                                  Hash(Target.Node.Value)}});
                } else {
                    try {
                        /* If variable doesn't exist, then GetLocal will throw an error */
                        auto Item = Environment.GetLocal(Target.Node.Value);
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::stack_store,
                                                              (BytecodeStructure::InstructionParam) {Item.first}});
                    } catch (InternalException &E) {
                        try {
                            /* If variable doesn't exist, then GetStatic will throw an error */
                            auto Item = Environment.MainPackage.GetStatic(Target.Node.Value);
                            Result.push_back(
                                    (BytecodeStructure) {BytecodeStructure::InstructionEnum::stack_store_static,
                                                         (BytecodeStructure::InstructionParam) {Item.first}});
                        } catch (InternalException &E) {
                            throw CompilerError(Target.Node.Line, Target.Node.Column, string2wstring(E.what()));
                        }
                    }
                }
                break;
            }
            case AST::TreeType::IndexExpression: {
                XArray<BytecodeStructure> Index = Generate(Target.Subtrees[1]);
                MergeArray(Result, Index);
                Result.push_back(
                        (BytecodeStructure) {BytecodeStructure::InstructionEnum::list_get_member,
                                             (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                break;
            }
            case AST::TreeType::FunctionCallingExpression: {
                /* TODO: Complete here. */
                break;
            }
            case AST::TreeType::MemberExpression: {
                MergeArray(Result, ParseMemberExpressionEndWithAssignment(Target.Subtrees[0], IsMemberExpression));
                MergeArray(Result, ParseMemberExpressionEndWithAssignment(Target.Subtrees[2], true));
                break;
            }

            default:
                throw CompilerError(Target.GetFirstNotNullToken().Line,
                                    Target.GetFirstNotNullToken().Column,
                                    L"ParserMemberExpression: Unexpected AST Type");
        }
        return Result;
    }
} // Compiler