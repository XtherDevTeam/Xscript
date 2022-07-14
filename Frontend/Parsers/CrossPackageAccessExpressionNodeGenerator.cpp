//
// Created by chou on 22-7-13.
//

#include "CrossPackageAccessExpressionNodeGenerator.hpp"
#include "MemberExpressionNodeGenerator.hpp"

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
            if (L.LastToken.Kind != Lexer::TokenKind::LeftBraces)
                MakeException(L"CrossPackageAccessExpressionNodeGenerator: Expected a left braces.");
            L.Scan();

            if (L.LastToken.Kind != Lexer::TokenKind::String)
                MakeException(L"CrossPackageAccessExpressionNodeGenerator: Expected a string value for package name.");
            AST PkgName{AST::TreeType::Primary, L.LastToken};
            L.Scan();

            if (L.LastToken.Kind != Lexer::TokenKind::RightBraces)
                MakeException(L"CrossPackageAccessExpressionNodeGenerator: Expected a right braces.");
            L.Scan();

            if (L.LastToken.Kind != Lexer::TokenKind::ToSign)
                MakeException(L"CrossPackageAccessExpressionNodeGenerator: Expected a `->`");
            L.Scan();

            AST MemberExpression = MemberExpressionNodeGenerator(L).Parse();
            if (MemberExpression.IsNotMatchNode())
                MakeException(L"CrossPackageAccessExpressionNodeGenerator: Expected a member expression");

            return {AST::TreeType::CrossPackageAccessExpression, {PkgName, MemberExpression}};
        }
    } // XScript
} // Generator