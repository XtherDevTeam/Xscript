//
// Created by Jerry Chou on 2022/5/21.
//

#include "ExpressionCompiler.hpp"
#include "../../Share/Exceptions/InternalException.hpp"
#include "../../Share/Exceptions/CompilerError.hpp"
#include "StatementCompiler.hpp"

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
            case AST::TreeType::MemberExpression:
            case AST::TreeType::CrossPackageAccessExpression: {
                MergeArray(Result, ParseMemberExpression(Target, false));
                Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::object_lvalue2rvalue,
                                                      (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                break;
            }
            case AST::TreeType::Primary: {
                switch (Target.Node.Kind) {
                    case Lexer::TokenKind::String:
                        Result.push_back(
                                (BytecodeStructure) {BytecodeStructure::InstructionEnum::constants_load,
                                                     (BytecodeStructure::InstructionParam) {
                                                             Environment.MainPackage.Constants.Push(
                                                                     (ConstantPool::ItemStructure) {
                                                                             Target.Node.Value})}});
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
            case AST::TreeType::ListLiteral: {
                for (auto &Item: Target.Subtrees) {
                    MergeArray(Result, Generate(Item));
                }
                Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::list_new,
                                                      (BytecodeStructure::InstructionParam) {
                                                              (XIndexType) Target.Subtrees.size()}});

                break;
            }
            case AST::TreeType::UnnamedFunctionDefinition: {
                XArray<XString> Params;

                XArray<BytecodeStructure> Structure;

                /**
                 * initialize params
                 */
                for (auto &I: Target.Subtrees[0].Subtrees) {
                    Params.push_back(I.Node.Value);
                }

                CompilingTimeFunction Func{
                        XArray<CompilingTimeFunction::Descriptor>{CompilingTimeFunction::Descriptor::Public}, Params,
                        {}};

                auto FuncIndex = Environment.MainPackage.PushUnnamedFunction(Func);

                /**
                 * Push function pointer to stack
                 */

                Result.push_back((BytecodeStructure) {
                        BytecodeStructure::InstructionEnum::stack_push_function,
                        (BytecodeStructure::InstructionParam) {Hash(Environment.MainPackage.Functions[FuncIndex].first)}
                });

                auto Backup = Environment.Locals;
                Environment.Locals = {};
                for (auto &I: Target.Subtrees[0].Subtrees) {
                    Environment.PushLocal(I.Node.Value, {(Typename) {Typename::TypenameKind::Unknown}, {}});
                }

                Structure = StatementCompiler(Environment).GenerateForCodeBlock(Target.Subtrees[1]);

                Environment.Locals = Backup;

                Environment.MainPackage.Functions[FuncIndex].second.BytecodeArray = Structure;
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
                switch (Target.Subtrees[1].Node.Kind) {
                    case Lexer::TokenKind::AdditionAssignment:
                        MergeArray(Result, Generate(Target.Subtrees[0]));
                        MergeArray(Result, Generate(Target.Subtrees[2]));
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::calculation_add,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    case Lexer::TokenKind::SubtractionAssignment:
                        MergeArray(Result, Generate(Target.Subtrees[0]));
                        MergeArray(Result, Generate(Target.Subtrees[2]));
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::calculation_sub,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    case Lexer::TokenKind::MultiplicationAssignment:
                        MergeArray(Result, Generate(Target.Subtrees[0]));
                        MergeArray(Result, Generate(Target.Subtrees[2]));
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::calculation_mul,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    case Lexer::TokenKind::DivisionAssignment:
                        MergeArray(Result, Generate(Target.Subtrees[0]));
                        MergeArray(Result, Generate(Target.Subtrees[2]));
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::calculation_div,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    case Lexer::TokenKind::RemainderAssignment:
                        MergeArray(Result, Generate(Target.Subtrees[0]));
                        MergeArray(Result, Generate(Target.Subtrees[2]));
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::calculation_mod,
                                                              (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                        break;
                    default:
                        MergeArray(Result, Generate(Target.Subtrees[2]));
                        break;
                }

                MergeArray(Result, ParseMemberExpressionEndWithAssignment(Target.Subtrees[0], false));
                break;
            }
            case AST::TreeType::NewExpression: {
                MergeArray(Result, ParseNewExpression(Target));
                break;
            }
            case AST::TreeType::InstanceOfExpression: {
                MergeArray(Result, Generate(Target.Subtrees[0]));
                if (Target.Subtrees[1].Type == AST::TreeType::Identifier) {
                    Result.push_back((BytecodeStructure) {
                            BytecodeStructure::InstructionEnum::class_instance_of,
                            (BytecodeStructure::InstructionParam) {
                                    Environment.MainPackage.GetClass(Target.Subtrees[1].Node.Value).first}
                    });
                } else if (Target.Subtrees[1].Type == AST::TreeType::CrossPackageAccessExpression) {
                    auto Pkg = Environment.GetPackage(Hash(Target.Subtrees[1].Subtrees[0].Node.Value));
                    Result.push_back((BytecodeStructure) {
                            BytecodeStructure::InstructionEnum::pc_get_current_package_id,
                            (BytecodeStructure::InstructionParam) {
                                    (XIndexType) {}}
                    });
                    Result.push_back((BytecodeStructure) {
                            BytecodeStructure::InstructionEnum::pc_set_current_package_id,
                            (BytecodeStructure::InstructionParam) {Pkg.first}
                    });
                    Result.push_back((BytecodeStructure) {
                            BytecodeStructure::InstructionEnum::class_instance_of,
                            (BytecodeStructure::InstructionParam) {
                                    (XIndexType) {Pkg.second.GetClass(Target.Subtrees[1].Subtrees[1].Node.Value).first}}
                    });
                    Result.push_back((BytecodeStructure) {
                            BytecodeStructure::InstructionEnum::pc_restore_package_id,
                            (BytecodeStructure::InstructionParam) {
                                    (XIndexType) {}}
                    });
                }
                break;
            }
            default:
                throw XScript::CompilerError(Target.GetFirstNotNullToken().Line,
                                             Target.GetFirstNotNullToken().Column,
                                             L"ExpressionCompiler: Unexpected AST Type");
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
                            if (Environment.InWhichPackage) {
                                auto Item = Environment.GetPackage(Environment.InWhichPackage).second.GetStatic(
                                        Target.Node.Value);
                                Result.push_back(
                                        (BytecodeStructure) {BytecodeStructure::InstructionEnum::static_get,
                                                             (BytecodeStructure::InstructionParam) {Item.first}});
                            } else {
                                auto Item = Environment.MainPackage.GetStatic(Target.Node.Value);
                                Result.push_back(
                                        (BytecodeStructure) {BytecodeStructure::InstructionEnum::static_get,
                                                             (BytecodeStructure::InstructionParam) {Item.first}});
                            }
                        } catch (InternalException &E) {
                            throw CompilerError(Target.Node.Line, Target.Node.Column, string2wstring(E.what()));
                        }
                    }
                }
                break;
            }
            case AST::TreeType::IndexExpression: {
                XArray<BytecodeStructure> Index = Generate(Target.Subtrees[1]);
                XArray<BytecodeStructure> Node = ParseMemberExpression(Target.Subtrees[0], IsMemberExpression);
                MergeArray(Result, Index);
                MergeArray(Result, Node);
                Result.push_back(
                        (BytecodeStructure) {BytecodeStructure::InstructionEnum::list_get_member,
                                             (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                break;
            }
            case AST::TreeType::FunctionCallingExpression: {
                if (!IsMemberExpression) {
                    for (auto &I: Target.Subtrees[1].Subtrees) {
                        MergeArray(Result, Generate(I));
                    }

                    /* let the executor get the function address first */
                    MergeArray(Result, Generate(Target.Subtrees[0]));

                    Result.push_back((BytecodeStructure) {
                            BytecodeStructure::InstructionEnum::func_invoke,
                            (BytecodeStructure::InstructionParam) {(XHeapIndexType) Target.Subtrees[1].Subtrees.size()}
                    });
                } else {
                    for (auto &I: Target.Subtrees[1].Subtrees) {
                        MergeArray(Result, Generate(I));
                    }

                    /* get `this` */
                    Result.push_back((BytecodeStructure) {
                            BytecodeStructure::InstructionEnum::stack_get_top,
                            (BytecodeStructure::InstructionParam) {(XIndexType) {Target.Subtrees[1].Subtrees.size()}}
                    });

                    /* let the executor get the function address first */
                    MergeArray(Result, ParseMemberExpression(Target.Subtrees[0], IsMemberExpression));
                    /* get the function pointer not heap index */
                    Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::object_lvalue2rvalue,
                                                          (BytecodeStructure::InstructionParam) {(XIndexType) 0}});

                    Result.push_back((BytecodeStructure) {
                            BytecodeStructure::InstructionEnum::func_invoke,
                            (BytecodeStructure::InstructionParam) {
                                    (XHeapIndexType) Target.Subtrees[1].Subtrees.size() + 1}
                    });
                }
                break;
            }
            case AST::TreeType::MemberExpression: {
                try {
                    if (Environment.InWhichPackage) {
                        Environment.GetPackage(Environment.InWhichPackage).second.GetClass(
                                Target.Subtrees[0].Node.Value);
                    } else {
                        Environment.MainPackage.GetClass(Target.Subtrees[0].Node.Value);
                    }
                    CompilingTimeClass *Dummy = nullptr;
                    MergeArray(Result, ParseClassMethodInvoke(Target, Dummy, false));
                } catch (InternalException &E) {
                    MergeArray(Result, ParseMemberExpression(Target.Subtrees[0], IsMemberExpression));
                    MergeArray(Result, ParseMemberExpression(Target.Subtrees[1], true));
                }
                break;
            }
            case AST::TreeType::CrossPackageAccessExpression: {
                Result.push_back((BytecodeStructure) {
                        BytecodeStructure::InstructionEnum::pc_get_current_package_id,
                        (BytecodeStructure::InstructionParam) {(XHeapIndexType) {}}
                });
                XIndexType Backup = Environment.InWhichPackage;
                Environment.InWhichPackage = Hash(Target.Subtrees[0].Node.Value);

                Result.push_back((BytecodeStructure) {
                        BytecodeStructure::InstructionEnum::pc_set_current_package_id,
                        (BytecodeStructure::InstructionParam) {(XHeapIndexType) {Environment.InWhichPackage}}
                });

                MergeArray(Result, ParseMemberExpression(Target.Subtrees[1], false));

                Environment.InWhichPackage = Backup;

                /* ??????????????? */
                /* restore_package_id ??????????????????????????????????????????????????????package_id */
                Result.push_back((BytecodeStructure) {
                        BytecodeStructure::InstructionEnum::pc_restore_package_id,
                        (BytecodeStructure::InstructionParam) {(XHeapIndexType) {}}
                });

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
                    Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::class_get_member,
                                                          (BytecodeStructure::InstructionParam) {
                                                                  Hash(Target.Node.Value)}});

                    Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::object_store,
                                                          (BytecodeStructure::InstructionParam) {
                                                                  (BytecodeStructure::InstructionParam) {
                                                                          (XHeapIndexType) 0}}});
                } else {
                    try {
                        /* If variable doesn't exist, then GetLocal will throw an error */
                        auto Item = Environment.GetLocal(Target.Node.Value);
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::stack_store,
                                                              (BytecodeStructure::InstructionParam) {Item.first}});
                    } catch (InternalException &E) {
                        try {
                            /* If variable doesn't exist, then GetStatic will throw an error */
                            if (Environment.InWhichPackage) {
                                auto Item = Environment.GetPackage(Environment.InWhichPackage).second.GetStatic(
                                        Target.Node.Value);
                                Result.push_back(
                                        (BytecodeStructure) {BytecodeStructure::InstructionEnum::static_store,
                                                             (BytecodeStructure::InstructionParam) {Item.first}});
                            } else {
                                auto Item = Environment.MainPackage.GetStatic(Target.Node.Value);
                                Result.push_back(
                                        (BytecodeStructure) {BytecodeStructure::InstructionEnum::static_store,
                                                             (BytecodeStructure::InstructionParam) {Item.first}});
                            }
                        } catch (InternalException &E) {
                            throw CompilerError(Target.Node.Line, Target.Node.Column, string2wstring(E.what()));
                        }
                    }
                }
                break;
            }
            case AST::TreeType::IndexExpression: {
                XArray<BytecodeStructure> Index = Generate(Target.Subtrees[1]);
                XArray<BytecodeStructure> Node = ParseMemberExpression(Target.Subtrees[0], IsMemberExpression);
                MergeArray(Result, Index);
                MergeArray(Result, Node);
                Result.push_back(
                        (BytecodeStructure) {BytecodeStructure::InstructionEnum::list_get_member,
                                             (BytecodeStructure::InstructionParam) {(XIndexType) 0}});
                Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::object_store,
                                                      (BytecodeStructure::InstructionParam) {
                                                              (XHeapIndexType) 0}});
                break;
            }
            case AST::TreeType::FunctionCallingExpression: {
                if (!IsMemberExpression) {
                    MergeArray(Result, Generate(Target.Subtrees[0]));

                    for (auto &I: Target.Subtrees[1].Subtrees) {
                        MergeArray(Result, Generate(I));
                    }
                    Result.push_back((BytecodeStructure) {
                            BytecodeStructure::InstructionEnum::func_invoke,
                            (BytecodeStructure::InstructionParam) {(XHeapIndexType) Target.Subtrees[1].Subtrees.size()}
                    });
                    Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::object_store,
                                                          (BytecodeStructure::InstructionParam) {
                                                                  (XHeapIndexType) 0}});
                } else {
                    for (auto &I: Target.Subtrees[1].Subtrees) {
                        MergeArray(Result, Generate(I));
                    }


                    /* get `this` */
                    Result.push_back((BytecodeStructure) {
                            BytecodeStructure::InstructionEnum::stack_get_top,
                            (BytecodeStructure::InstructionParam) {(XIndexType) {Target.Subtrees[1].Subtrees.size()}}
                    });

                    /* let the executor get the function address first */
                    MergeArray(Result, ParseMemberExpression(Target.Subtrees[0], IsMemberExpression));
                    /* get the function pointer not heap index */
                    Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::object_lvalue2rvalue,
                                                          (BytecodeStructure::InstructionParam) {(XIndexType) 0}});

                    Result.push_back((BytecodeStructure) {
                            BytecodeStructure::InstructionEnum::func_invoke,
                            (BytecodeStructure::InstructionParam) {
                                    (XHeapIndexType) Target.Subtrees[1].Subtrees.size() + 1}
                    });
                    Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::object_store,
                                                          (BytecodeStructure::InstructionParam) {
                                                                  (XHeapIndexType) 0}});
                }
                break;
            }
            case AST::TreeType::MemberExpression: {
                try {
                    if (Environment.InWhichPackage) {
                        Environment.GetPackage(Environment.InWhichPackage).second.GetClass(
                                Target.Subtrees[0].Node.Value);
                    } else {
                        Environment.MainPackage.GetClass(Target.Subtrees[0].Node.Value);
                    }
                    CompilingTimeClass *Dummy = nullptr;
                    MergeArray(Result, ParseClassMethodInvoke(Target, Dummy, false));
                    Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::object_store,
                                                          (BytecodeStructure::InstructionParam) {
                                                                  (BytecodeStructure::InstructionParam) {
                                                                          (XHeapIndexType) 0}}});
                } catch (InternalException &E) {
                    MergeArray(Result, ParseMemberExpression(Target.Subtrees[0], IsMemberExpression));
                    MergeArray(Result, ParseMemberExpressionEndWithAssignment(Target.Subtrees[1], true));
                }
                break;
            }
            case AST::TreeType::CrossPackageAccessExpression: {
                Result.push_back((BytecodeStructure) {
                        BytecodeStructure::InstructionEnum::pc_get_current_package_id,
                        (BytecodeStructure::InstructionParam) {(XHeapIndexType) {}}
                });
                XIndexType Backup = Environment.InWhichPackage;
                Environment.InWhichPackage = Hash(Target.Subtrees[0].Node.Value);

                Result.push_back((BytecodeStructure) {
                        BytecodeStructure::InstructionEnum::pc_set_current_package_id,
                        (BytecodeStructure::InstructionParam) {(XHeapIndexType) {Environment.InWhichPackage}}
                });

                MergeArray(Result, ParseMemberExpressionEndWithAssignment(Target.Subtrees[1], false));

                Environment.InWhichPackage = Backup;

                /* ??????????????? */
                /* restore_package_id ??????????????????????????????????????????????????????package_id */
                Result.push_back((BytecodeStructure) {
                        BytecodeStructure::InstructionEnum::pc_restore_package_id,
                        (BytecodeStructure::InstructionParam) {(XHeapIndexType) {}}
                });

                break;
            }

            default:
                throw CompilerError(Target.GetFirstNotNullToken().Line,
                                    Target.GetFirstNotNullToken().Column,
                                    L"ParseMemberExpressionEndWithAssignment: Unexpected AST Type");
        }

        return Result;
    }

    XArray<BytecodeStructure>
    ExpressionCompiler::ParseClassMethodInvoke(AST &Target, CompilingTimeClass *&IsInParsing,
                                               bool ReservedStackItemForThisPointer) {
        XArray<BytecodeStructure> Result;
        switch (Target.Type) {
            case AST::TreeType::FunctionCallingExpression: {
                /* MemberExpression??????????????????????????????????????????IsInParsing????????? */
                /* ??????????????????????????????????????????this?????? */
                for (auto &I: Target.Subtrees[1].Subtrees) {
                    MergeArray(Result, Generate(I));
                }

                if (IsInParsing == nullptr) {
                    MergeArray(Result,
                               ParseClassMethodInvoke(Target.Subtrees[0], IsInParsing,
                                                      ReservedStackItemForThisPointer));

                    XIndexType Index = IsInParsing->IsMethodExist(
                            IsInParsing->ClassName + L"$constructor");
                    if (Index == -1) {
                        throw CompilerError(Target.GetFirstNotNullToken().Line,
                                            Target.GetFirstNotNullToken().Column,
                                            L"ParseClassMethodInvoke: Cannot find default constructor in this class");
                    }

                    Result.push_back((BytecodeStructure) {
                            BytecodeStructure::InstructionEnum::stack_push_function,
                            (BytecodeStructure::InstructionParam) Hash(IsInParsing->Methods[Index].second)
                    });
                } else {
                    /* let the executor get the function address first */
                    XIndexType Index = IsInParsing->IsMethodExist(
                            IsInParsing->ClassName + L"$" + Target.Subtrees[0].Node.Value);
                    if (Index == -1) {
                        throw CompilerError(Target.GetFirstNotNullToken().Line,
                                            Target.GetFirstNotNullToken().Column,
                                            L"ParseClassMethodInvoke: ???????????????????????????????????????????????????????????????????????? " +
                                            Target.Subtrees[0].Node.Value + L" ???????????????????????????");
                    }

                    Result.push_back((BytecodeStructure) {
                            BytecodeStructure::InstructionEnum::stack_push_function,
                            (BytecodeStructure::InstructionParam) Hash(IsInParsing->Methods[Index].second)
                    });
                }

                /* ???????????????this???????????? */
                Result.push_back((BytecodeStructure) {
                        BytecodeStructure::InstructionEnum::func_invoke,
                        (BytecodeStructure::InstructionParam) {(XHeapIndexType) Target.Subtrees[1].Subtrees.size() +
                                                               (ReservedStackItemForThisPointer ? 1 : 0)}
                });
                break;
            }
            case AST::TreeType::Identifier: {
                if (IsInParsing) {
                    XIndexType Index = IsInParsing->IsMethodExist(Target.Node.Value);
                    if (Index != -1) {
                        Result.push_back((BytecodeStructure) {
                                BytecodeStructure::InstructionEnum::stack_push_function,
                                (BytecodeStructure::InstructionParam) Hash(IsInParsing->Methods[Index].second)
                        });
                        break;
                    } else {
                        throw CompilerError(Target.GetFirstNotNullToken().Line,
                                            Target.GetFirstNotNullToken().Column,
                                            L"ParseClassMethodInvoke: ???????????????????????????????????????????????????????????????????????? " +
                                            Target.Node.Value + L" ???????????????????????????");
                    }
                } else {
                    try {
                        if (Environment.InWhichPackage) {
                            CompilingTimeClass &Class = Environment.GetPackage(
                                    Environment.InWhichPackage).second.GetClass(Target.Node.Value).second;
                            IsInParsing = &Class;
                        } else {
                            CompilingTimeClass &Class = Environment.MainPackage.GetClass(Target.Node.Value).second;
                            IsInParsing = &Class;
                        }
                    } catch (InternalException &E) {
                        throw CompilerError(Target.GetFirstNotNullToken().Line,
                                            Target.GetFirstNotNullToken().Column,
                                            L"ParseClassMethodInvoke: ????????????????????? " +
                                            Target.Node.Value +
                                            L" ???????????????????????????????????????. ???????????????????????????????????????????????????");
                    }
                }
                break;
            }
            case AST::TreeType::MemberExpression: {
                if (Target.Subtrees[0].Node.Kind != Lexer::TokenKind::Identifier or
                    (Target.Subtrees[1].Type != AST::TreeType::FunctionCallingExpression and
                     Target.Subtrees[1].Node.Kind != Lexer::TokenKind::Identifier)) {
                    throw CompilerError(Target.GetFirstNotNullToken().Line,
                                        Target.GetFirstNotNullToken().Column,
                                        L"ParseClassMethodInvoke: ????????????????????????????????????????????????????????????");
                }
                MergeArray(Result,
                           ParseClassMethodInvoke(Target.Subtrees[0], IsInParsing, ReservedStackItemForThisPointer));
                MergeArray(Result,
                           ParseClassMethodInvoke(Target.Subtrees[1], IsInParsing, ReservedStackItemForThisPointer));
                break;
            }
            case AST::TreeType::CrossPackageAccessExpression: {
                Result.push_back((BytecodeStructure) {
                        BytecodeStructure::InstructionEnum::pc_get_current_package_id,
                        (BytecodeStructure::InstructionParam) {(XHeapIndexType) {}}
                });
                XIndexType Backup = Environment.InWhichPackage;
                Environment.InWhichPackage = Hash(Target.Subtrees[0].Node.Value);

                Result.push_back((BytecodeStructure) {
                        BytecodeStructure::InstructionEnum::pc_set_current_package_id,
                        (BytecodeStructure::InstructionParam) {(XHeapIndexType) {Environment.InWhichPackage}}
                });

                MergeArray(Result,
                           ParseClassMethodInvoke(Target.Subtrees[1], IsInParsing, ReservedStackItemForThisPointer));

                Environment.InWhichPackage = Backup;

                /* ??????????????? */
                /* restore_package_id ??????????????????????????????????????????????????????package_id */
                Result.push_back((BytecodeStructure) {
                        BytecodeStructure::InstructionEnum::pc_restore_package_id,
                        (BytecodeStructure::InstructionParam) {(XHeapIndexType) {}}
                });

                break;
            }
            default: {
                throw CompilerError(Target.GetFirstNotNullToken().Line,
                                    Target.GetFirstNotNullToken().Column,
                                    L"ParseClassMethodInvoke: Unexpected AST Type");
            }
        }
        return Result;
    }

    XArray<BytecodeStructure> ExpressionCompiler::ParseNewExpression(AST &Target) {
        XArray<BytecodeStructure> Result;
        Lexer::Token ClassName = Target.Subtrees[0].Subtrees[0].Node;
        try {
            if (Environment.InWhichPackage) {
                CompilingTimeClass &Class = Environment.GetPackage(
                        Environment.InWhichPackage).second.GetClass(ClassName.Value).second;
            } else {
                CompilingTimeClass &Class = Environment.MainPackage.GetClass(ClassName.Value).second;
            }
        } catch (InternalException &E) {
            throw CompilerError(Target.GetFirstNotNullToken().Line,
                                Target.GetFirstNotNullToken().Column,
                                L"ParseNewExpression: ????????????????????? " +
                                ClassName.Value +
                                L" ???????????????????????????????????????. ???????????????????????????????????????????????????");
        }

        Result.push_back((BytecodeStructure) {
                BytecodeStructure::InstructionEnum::class_new,
                (BytecodeStructure::InstructionParam) {Hash(ClassName.Value)}
        });
        /* ????????????????????? this?????? */
        Result.push_back((BytecodeStructure) {
                BytecodeStructure::InstructionEnum::stack_get_top,
                (BytecodeStructure::InstructionParam) {(XHeapIndexType) {}}
        });

        CompilingTimeClass *Dummy = nullptr;
        MergeArray(Result, ParseClassMethodInvoke(Target.Subtrees[0], Dummy, true));

        Result.push_back((BytecodeStructure) {
                BytecodeStructure::InstructionEnum::stack_pop,
                (BytecodeStructure::InstructionParam) {(XHeapIndexType) {}}
        });
        return Result;
    }
} // Compiler