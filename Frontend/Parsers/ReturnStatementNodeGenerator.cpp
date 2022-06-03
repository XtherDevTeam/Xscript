//
// Created by Jerry Chou on 2022/6/3.
//

#include "ReturnStatementNodeGenerator.hpp"
#include "ExpressionNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        ReturnStatementNodeGenerator::ReturnStatementNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST ReturnStatementNodeGenerator::Parse() {
            if (L.LastToken == (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"return", 0, 0}) {
                L.Scan();
                AST Expression = ExpressionNodeGenerator(L).Parse();
                if (Expression.IsNotMatchNode() or Expression.Type == AST::TreeType::AssignmentExpression) {
                    MakeException(L"ReturnStatementNodeGenerator: InvalidSyntax -> Expected a lvalue expression.");
                }
                return {AST::TreeType::ReturnStatement, {Expression}};
            } else {
                Rollback();
                return {};
            }
        }
    } // XScript
} // Generator