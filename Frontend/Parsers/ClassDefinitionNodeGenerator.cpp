//
// Created by Jerry Chou on 2022/6/2.
//

#include "ClassDefinitionNodeGenerator.hpp"
#include "IdentifierNodeGenerator.hpp"
#include "MethodDefinitionNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        ClassDefinitionNodeGenerator::ClassDefinitionNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST ClassDefinitionNodeGenerator::Parse() {
            if (L.LastToken == (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"class", 0, 0}) {
                L.Scan();
                if (L.LastToken.Kind != Lexer::TokenKind::Identifier)
                    MakeException(L"ClassDefinitionNodeGenerator: InvalidSyntax -> Expected an identifier");
                AST Name = {AST::TreeType::Identifier, L.LastToken};
                L.Scan();
                AST Extends{AST::TreeType::ClassExtends, (XArray<AST>) {}};
                if (L.LastToken == (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"extends", 0, 0}) {
                    L.Scan();

                    AST ExtendName = IdentifierNodeGenerator(L).Parse();

                    if (ExtendName.IsNotMatchNode())
                        MakeException(L"ClassDefinitionNodeGenerator: InvalidSyntax -> Expected a identifier");

                    Extends.Subtrees.push_back(ExtendName);
                }

                if (L.LastToken.Kind != Lexer::TokenKind::LeftBraces)
                    MakeException(L"ClassDefinitionNodeGenerator: InvalidSyntax -> Expected a left braces");
                L.Scan();

                AST ClassInnerStmts{AST::TreeType::ClassInnerStatements, (XArray<AST>) {}};
                for (AST Stmt = MethodDefinitionNodeGenerator(L).Parse(); !Stmt.IsNotMatchNode();
                     Stmt = MethodDefinitionNodeGenerator(L).Parse()) {
                    ClassInnerStmts.Subtrees.push_back(Stmt);
                }

                if (L.LastToken.Kind != Lexer::TokenKind::RightBraces)
                    MakeException(L"ClassDefinitionNodeGenerator: InvalidSyntax -> Expected a right braces");
                L.Scan();

                return {AST::TreeType::ClassDefinition, {Name, Extends, ClassInnerStmts}};
            } else {
                Rollback();
                return {};
            }
        }
    } // XScript
} // Generator