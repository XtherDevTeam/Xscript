//
// Created by Jerry Chou on 2022/5/21.
//

#include "PrimaryNodeGenerator.hpp"
#include "ListLiteralNodeGenerator.hpp"

namespace XScript::Generator {
    PrimaryNodeGenerator::PrimaryNodeGenerator(Lexer &L) : BaseGenerator(L) {

    }

    AST PrimaryNodeGenerator::Parse() {
        if (L.LastToken.Kind == Lexer::TokenKind::Integer or L.LastToken.Kind == Lexer::TokenKind::Decimal or
            L.LastToken.Kind == Lexer::TokenKind::Boolean or L.LastToken.Kind == Lexer::TokenKind::String) {
            AST Result = {AST::TreeType::Primary, L.LastToken};
            L.Scan(); // prepare for next time.
            return Result;
        } else if (L.LastToken.Kind == Lexer::TokenKind::LeftParentheses) {
            AST Expr = ExpressionNodeGenerator(L).Parse();
            if (Expr.IsNotMatchNode())
                return Expr;
            if (L.LastToken.Kind != Lexer::TokenKind::RightParentheses)
                MakeException(L"PrimaryNodeGenerator: InvalidSyntax -> Expected a right parentheses");
            L.Scan();

            return Expr;
        } else if (L.LastToken.Kind == Lexer::TokenKind::LeftBracket) {
            AST List = ListLiteralNodeGenerator(L).Parse();
            return List;
        }
        Rollback();
        return {};
    }
} // Generator