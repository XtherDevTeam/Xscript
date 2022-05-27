//
// Created by Jerry Chou on 2022/5/26.
//

#include "CodeBlockNodeGenerator.hpp"
#include "StatementNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        CodeBlockNodeGenerator::CodeBlockNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST CodeBlockNodeGenerator::Parse() {
            AST Result{AST::TreeType::CodeBlockStatement, (XArray<AST>) {}};

            if (L.LastToken.Kind != Lexer::TokenKind::LeftBraces) {
                Rollback();
                return {};
            }
            L.Scan();

            AST Temp = StatementNodeGenerator(L).Parse();
            while (!Temp.IsNotMatchNode()) {
                Result.Subtrees.push_back(Temp);

                if (L.LastToken.Kind != Lexer::TokenKind::Semicolon) {
                    switch (Temp.Type) {
                        case AST::TreeType::IfStatement:
                        case AST::TreeType::IfElseStatement:
                        case AST::TreeType::WhileStatement:
                        case AST::TreeType::ForStatement:
                        case AST::TreeType::CodeBlockStatement: {
                            break;
                        }
                        default: {
                            MakeException(L"CodeBlockNodeGenerator: Expected a semicolon after this statement");
                            break;
                        }
                    }
                } else {
                    L.Scan();
                }
                Temp = StatementNodeGenerator(L).Parse();
            }

            if (L.LastToken.Kind != Lexer::TokenKind::RightBraces) {
                Rollback();
                return {};
            }
            L.Scan();
            return Result;

        }
    } // XScript
} // Generator