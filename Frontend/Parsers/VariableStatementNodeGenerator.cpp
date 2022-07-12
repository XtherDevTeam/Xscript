//
// Created by Jerry Chou on 2022/5/24.
//

#include "VariableStatementNodeGenerator.hpp"
#include "ExpressionNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        VariableStatementNodeGenerator::VariableStatementNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST VariableStatementNodeGenerator::Parse() {
            if (L.LastToken == (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"var", 0, 0}) {
                L.Scan();
                if (L.LastToken.Kind != Lexer::TokenKind::Identifier) {
                    Rollback();
                    MakeException(L"VariableStatementNodeGenerator: InvalidSyntax");
                }
                AST Name = {AST::TreeType::Identifier, L.LastToken};
                L.Scan();
                if (L.LastToken.Kind != Lexer::TokenKind::AssignSign) {
                    return {AST::TreeType::VariableDeclaration, (XArray<AST>) {Name}};
                }
                L.Scan();
                AST Expression = ExpressionNodeGenerator(L).Parse();
                if (Expression.IsNotMatchNode()) {
                    Rollback();
                    MakeException(L"VariableStatementNodeGenerator: InvalidSyntax");
                }
                return {AST::TreeType::VariableDefinition, {Name, Expression}};
            } else {
                Rollback();
                return {};
            }
        }
    } // XScript
} // Generator