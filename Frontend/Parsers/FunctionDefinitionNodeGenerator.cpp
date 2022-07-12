//
// Created by Jerry Chou on 2022/5/29.
//

#include "FunctionDefinitionNodeGenerator.hpp"
#include "ArgumentsNodeGenerator.hpp"
#include "CodeBlockNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        FunctionDefinitionNodeGenerator::FunctionDefinitionNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST FunctionDefinitionNodeGenerator::Parse() {
            if (L.LastToken != (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"def", 0, 0}) {
                L.Scan();
                if (L.LastToken.Kind != Lexer::TokenKind::Identifier) {
                    MakeException(L"FunctionDefinitionNodeGenerator: InvalidSyntax -> Expected an identifier");
                }
                AST Identifier = {AST::TreeType::Identifier, L.LastToken};
                L.Scan();
                AST Arguments = ArgumentsNodeGenerator(L).Parse();
                if (Arguments.IsNotMatchNode())
                    MakeException(L"FunctionDefinitionNodeGenerator: InvalidSyntax -> Expected an ArgumentsNode");
                for (auto &I: Arguments.Subtrees)
                    if (I.Type != AST::TreeType::Identifier)
                        MakeException(
                                L"FunctionDefinitionNodeGenerator: InvalidSyntax -> Expected an identifier for param");

                AST CodeBlock = CodeBlockNodeGenerator(L).Parse();
                if (CodeBlock.IsNotMatchNode())
                    MakeException(L"FunctionDefinitionNodeGenerator: InvalidSyntax -> Expected a CodeBlockNode");

                return {AST::TreeType::FunctionDefinition, {Identifier, Arguments, CodeBlock}};
            } else {
                Rollback();
                return {};
            }
        }
    } // XScript
} // Generator