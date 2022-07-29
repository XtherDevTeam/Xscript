//
// Created by XIaokang00010 on 2022/7/29.
//

#include "UnnamedFunctionDefinitionNodeGenerator.hpp"
#include "ArgumentsNodeGenerator.hpp"
#include "CodeBlockNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        UnnamedFunctionDefinitionNodeGenerator::UnnamedFunctionDefinitionNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST UnnamedFunctionDefinitionNodeGenerator::Parse() {
            if (L.LastToken != (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"func", 0, 0}) {
                return {};
            }
            L.Scan();
            AST Arguments = ArgumentsNodeGenerator(L).Parse();
            if (Arguments.IsNotMatchNode())
                MakeException(L"UnnamedFunctionDefinitionNodeGenerator: InvalidSyntax -> Expected an ArgumentsNode");
            for (auto &I: Arguments.Subtrees)
                if (I.Type != AST::TreeType::Identifier)
                    MakeException(
                            L"UnnamedFunctionDefinitionNodeGenerator: InvalidSyntax -> Expected an identifier for param");

            AST CodeBlock = CodeBlockNodeGenerator(L).Parse();
            if (CodeBlock.IsNotMatchNode())
                MakeException(L"UnnamedFunctionDefinitionNodeGenerator: InvalidSyntax -> Expected a CodeBlockNode");

            return {AST::TreeType::UnnamedFunctionDefinition, {Arguments, CodeBlock}};
        }
    } // XScript
} // Generator