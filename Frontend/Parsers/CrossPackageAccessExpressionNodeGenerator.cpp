//
// Created by Jerry Chou on 22-7-13.
//

#include "CrossPackageAccessExpressionNodeGenerator.hpp"
#include "IdentifierNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        CrossPackageAccessExpressionNodeGenerator::CrossPackageAccessExpressionNodeGenerator(Lexer &L) : BaseGenerator(
                L) {

        }

        AST CrossPackageAccessExpressionNodeGenerator::Parse() {
            if (L.LastToken != (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"@", 0, 0}) {
                return {};
            }
            L.Scan();
            if (L.LastToken.Kind != Lexer::TokenKind::LeftParentheses)
                MakeException(L"CrossPackageAccessExpressionNodeGenerator: Expected a left parentheses.");
            L.Scan();

            if (L.LastToken.Kind != Lexer::TokenKind::Identifier)
                MakeException(L"CrossPackageAccessExpressionNodeGenerator: Expected a identifier for package alias.");
            AST PkgName{AST::TreeType::Identifier, L.LastToken};
            L.Scan();

            if (L.LastToken.Kind != Lexer::TokenKind::RightParentheses)
                MakeException(L"CrossPackageAccessExpressionNodeGenerator: Expected a right parentheses.");
            L.Scan();

            if (L.LastToken.Kind != Lexer::TokenKind::Dot)
                MakeException(L"CrossPackageAccessExpressionNodeGenerator: Expected a `.`");
            L.Scan();

            AST MemberExpression = IdentifierNodeGenerator(L).Parse();
            if (MemberExpression.IsNotMatchNode())
                MakeException(L"CrossPackageAccessExpressionNodeGenerator: Expected a member expression");

            return {AST::TreeType::CrossPackageAccessExpression, {PkgName, MemberExpression}};
        }
    } // XScript
} // Generator