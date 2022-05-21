//
// Created by Jerry Chou on 2022/5/21.
//

#include "ExpressionCompiler.hpp"
#include "../../Share/Exceptions/InternalException.hpp"
#include "../../Share/Exceptions/CompilerError.hpp"

namespace XScript {
    namespace Compiler {
        ExpressionCompiler::ExpressionCompiler(CompilerEnvironment &Environment) : BaseCompiler(Environment) {

        }

        XArray<BytecodeStructure> ExpressionCompiler::Generate(AST &Target) {
            XArray<BytecodeStructure> Result;
            switch (Target.Type) {
                /* get variable lvalue and  */
                case AST::TreeType::Identifier:
                    break;
                case AST::TreeType::IndexExpression:
                    break;
                case AST::TreeType::FunctionCallingExpression:
                    break;
                case AST::TreeType::MemberExpression:
                    break;

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
                case AST::TreeType::NegativeExpression:

                    break;
                case AST::TreeType::IncrementExpression:
                    break;
                case AST::TreeType::DecrementExpression:
                    break;
                case AST::TreeType::MultiplicationExpression:
                    break;
                case AST::TreeType::AdditionExpression:
                    break;
                case AST::TreeType::BinaryMoveExpression:
                    break;
                case AST::TreeType::ComparingExpression:
                    break;
                case AST::TreeType::EqualExpression:
                    break;
                case AST::TreeType::BinaryExpression:
                    break;
                case AST::TreeType::LogicExpression:
                    break;
                case AST::TreeType::AssignmentExpression:
                    break;

                default:
                    throw XScript::CompilerError(Target.GetFirstNotNullToken().Line,
                                                 Target.GetFirstNotNullToken().Column, L"Unexpected AST Type");
            }
        }

        XArray<BytecodeStructure> ExpressionCompiler::ParseMemberExpression(AST &Target, XIndexType &ClassIndex) {
            XArray<BytecodeStructure> Result;

            switch (Target.Type) {
                case AST::TreeType::Identifier: {
                    try {
                        auto Item = Environment.GetLocal(Target.Node.Value);
                        Result.push_back((BytecodeStructure) {BytecodeStructure::InstructionEnum::stack_duplicate,
                                                              (BytecodeStructure::InstructionParam) {Item.first}});
                    } catch (InternalException &E) {

                    }
                    break;
                }
                case AST::TreeType::IndexExpression:
                    break;
                case AST::TreeType::FunctionCallingExpression:
                    break;
                case AST::TreeType::MemberExpression:
                    break;

                default:
                    throw CompilerError(Target.GetFirstNotNullToken().Line,
                                        Target.GetFirstNotNullToken().Column,
                                        L"ParserMemberExpression: Unexpected AST Type");
            }
        }
    } // XScript
} // Compiler