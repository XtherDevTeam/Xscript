//
// Created by Jerry Chou on 2022/5/27.
//

#include "WhileStatementNodeGenerator.hpp"
#include "ExpressionNodeGenerator.hpp"
#include "CodeBlockNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        WhileStatementNodeGenerator::WhileStatementNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST WhileStatementNodeGenerator::Parse() {
            if (L.LastToken == (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"while", 0, 0}) {
                L.Scan();

                if (L.LastToken.Kind != Lexer::TokenKind::LeftParentheses)
                    MakeException(L"WhileStatementNodeGenerator: InvalidSyntax -> Expected a left parentheses");
                L.Scan();

                AST Condition = ExpressionNodeGenerator(L).Parse();
                if (Condition.IsNotMatchNode() or Condition.Type == AST::TreeType::AssignmentExpression)
                    MakeException(L"WhileStatementNodeGenerator: InvalidSyntax -> Expected a lvalue expression");

                if (L.LastToken.Kind != Lexer::TokenKind::RightParentheses)
                    MakeException(L"WhileStatementNodeGenerator: InvalidSyntax -> Expected a right parentheses");
                L.Scan();

                AST CodeBlock = CodeBlockNodeGenerator(L).Parse();
                if (CodeBlock.IsNotMatchNode())
                    MakeException(L"WhileStatementNodeGenerator: InvalidSyntax -> Expected a code block");

                return {AST::TreeType::WhileStatement, {Condition, CodeBlock}};
            } else {
                Rollback();
                return {};
            }
        }
    } // XScript
} // Generator