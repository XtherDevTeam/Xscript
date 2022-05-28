//
// Created by Jerry Chou on 2022/5/28.
//

#include "ForStatementNodeGenerator.hpp"
#include "StatementNodeGenerator.hpp"
#include "ExpressionNodeGenerator.hpp"
#include "CodeBlockNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        ForStatementNodeGenerator::ForStatementNodeGenerator(Lexer &ZL) : BaseGenerator(ZL) {

        }

        AST ForStatementNodeGenerator::Parse() {
            if (L.LastToken == (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"for", 0, 0}) {
                L.Scan();
                if (L.LastToken.Kind != Lexer::TokenKind::LeftParentheses)
                    MakeException(L"ForStatementNodeGenerator: InvalidSyntax -> Expected a left parentheses");

                L.Scan();

                AST InitialStatement = StatementNodeGenerator(L).Parse();
                if (InitialStatement.IsNotMatchNode())
                    MakeException(L"ForStatementNodeGenerator: InvalidSyntax -> Expected a initial statement");

                if (L.LastToken.Kind != Lexer::TokenKind::Semicolon)
                    MakeException(L"ForStatementNodeGenerator: InvalidSyntax -> Expected a semicolon after initial statement");
                L.Scan();

                AST Condition = ExpressionNodeGenerator(L).Parse();
                if (Condition.IsNotMatchNode() or Condition.Type == AST::TreeType::AssignmentExpression)
                    MakeException(L"ForStatementNodeGenerator: InvalidSyntax -> Expected a condition expression");

                if (L.LastToken.Kind != Lexer::TokenKind::Semicolon)
                    MakeException(L"ForStatementNodeGenerator: InvalidSyntax -> Expected a semicolon after condition");
                L.Scan();

                AST AfterStatement = StatementNodeGenerator(L).Parse();
                if (AfterStatement.IsNotMatchNode())
                    MakeException(L"ForStatementNodeGenerator: InvalidSyntax -> Expected a after statement");

                if (L.LastToken.Kind != Lexer::TokenKind::RightParentheses)
                    MakeException(L"ForStatementNodeGenerator: InvalidSyntax -> Expected a right parentheses");
                L.Scan();

                AST CodeBlock = CodeBlockNodeGenerator(L).Parse();
                if (CodeBlock.IsNotMatchNode())
                    MakeException(L"ForStatementNodeGenerator: InvalidSyntax -> Expected a code block");

                return {AST::TreeType::ForStatement, {InitialStatement, Condition, AfterStatement, CodeBlock}};

            } else {
                Rollback();
                return {};
            }
        }
    } // XScript
} // Generator