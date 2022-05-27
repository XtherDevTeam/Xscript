//
// Created by Jerry Chou on 2022/5/26.
//

#include "IfStatementNodeGenerator.hpp"
#include "ExpressionNodeGenerator.hpp"
#include "CodeBlockNodeGenerator.hpp"
#include "StatementNodeGenerator.hpp"

namespace XScript {
    namespace Generator {

        AST IfStatementNodeGenerator::Parse() {
            if (L.LastToken == (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"if", 0, 0}) {
                L.Scan();
                if (L.LastToken.Kind != Lexer::TokenKind::LeftParentheses) {
                    MakeException(L"IfStatementNodeGenerator: InvalidSyntax");
                }
                L.Scan();
                AST Condition = ExpressionNodeGenerator(L).Parse();
                if (Condition.IsNotMatchNode() or Condition.Type == AST::TreeType::AssignmentExpression) {
                    MakeException(L"IfStatementGenerator: InvalidSyntax");
                }
                if (L.LastToken.Kind != Lexer::TokenKind::RightParentheses) {
                    MakeException(L"IfStatementNodeGenerator: InvalidSyntax");
                }
                L.Scan();

                AST CodeBlock = CodeBlockNodeGenerator(L).Parse();
                if (CodeBlock.IsNotMatchNode()) {
                    MakeException(L"IfStatementNodeGenerator: InvalidSyntax");
                }

                if (L.LastToken == (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"else", 0, 0}) {
                    L.Scan();
                    AST ElseBlock = StatementNodeGenerator(L).Parse();
                    return {AST::TreeType::IfElseStatement, {Condition, CodeBlock, ElseBlock}};
                }

                return {AST::TreeType::IfStatement, {Condition, CodeBlock}};
            } else {
                Rollback();
                return {};
            }
        }

        IfStatementNodeGenerator::IfStatementNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }
    } // XScript
} // Generator