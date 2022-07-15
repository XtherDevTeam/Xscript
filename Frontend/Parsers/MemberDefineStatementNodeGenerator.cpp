//
// Created by chou on 22-7-15.
//

#include "MemberDefineStatementNodeGenerator.hpp"
#include "ExpressionNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        MemberDefineStatementNodeGenerator::MemberDefineStatementNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST MemberDefineStatementNodeGenerator::Parse() {
            if (L.LastToken != (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"def", 0, 0}) {
                return {};
            }
            L.Scan();

            if (L.LastToken.Kind != Lexer::TokenKind::Identifier) {
                MakeException(L"MemberDefineStatementNodeGenerator::Parse(): Expected an identifier.");
            }
            AST Ident = {AST::TreeType::Identifier, L.LastToken};
            L.Scan();

            if (L.LastToken != (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"in", 0, 0}) {
                MakeException(L"MemberDefineStatementNodeGenerator::Parse(): Expected `in`.");
            }
            L.Scan();

            AST Expr = ExpressionNodeGenerator(L).Parse();
            if (Expr.IsNotMatchNode()) {
                MakeException(L"MemberDefineStatementNodeGenerator::Parse(): Expected a expression.");
            }

            return {AST::TreeType::MemberDefineStatement, {Ident, Expr}};
        }
    } // XScript
} // Generator