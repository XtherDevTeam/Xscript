//
// Created by Jerry Chou on 2022/5/28.
//

#include "ListLiteralNodeGenerator.hpp"
#include "ExpressionNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        ListLiteralNodeGenerator::ListLiteralNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST ListLiteralNodeGenerator::Parse() {
            if (L.LastToken.Kind == Lexer::TokenKind::LeftBracket) {
                L.Scan();
                AST Result = {AST::TreeType::ListLiteral, (XArray<AST>) {}};

                AST Temp = ExpressionNodeGenerator(L).Parse();
                while (!Temp.IsNotMatchNode()) {
                    Result.Subtrees.push_back(Temp);
                    if (L.LastToken.Kind != Lexer::TokenKind::Colon)
                        break;
                    L.Scan();
                    Temp = ExpressionNodeGenerator(L).Parse();
                }

                if (L.LastToken.Kind != Lexer::TokenKind::RightBracket)
                    MakeException(L"ListLiteralNodeGenerator: InvalidSyntax -> Expected a right bracket");
                L.Scan();

                return Result;
            } else {
                Rollback();
                return {};
            }
        }
    } // XScript
} // Generator