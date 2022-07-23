//
// Created by Jerry Chou on 22-7-14.
//

#include "NewExpressionNodeGenerator.hpp"
#include "MemberExpressionNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        NewExpressionNodeGenerator::NewExpressionNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST NewExpressionNodeGenerator::Parse() {
            if (L.LastToken != (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"new", 0, 0}) {
                return {};
            }
            L.Scan();
            AST MemberExpr = MemberExpressionNodeGenerator(L).Parse();
            if ((MemberExpr.Type != AST::TreeType::MemberExpression or
                MemberExpr.Subtrees[0].Type != AST::TreeType::Identifier or
                MemberExpr.Subtrees[1].Type != AST::TreeType::FunctionCallingExpression) and
                MemberExpr.Type != AST::TreeType::FunctionCallingExpression) {
                MakeException(
                        L"NewExpressionNodeGenerator::Parse(): Expected a function calling expression with member expression.");
            }
            return {AST::TreeType::NewExpression, {MemberExpr}};
        }
    } // XScript
} // Generator