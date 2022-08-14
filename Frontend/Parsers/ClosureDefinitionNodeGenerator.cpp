//
// Created by p0010 on 22-8-14.
//

#include "ClosureDefinitionNodeGenerator.hpp"
#include "CodeBlockNodeGenerator.hpp"
#include "ArgumentsNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        ClosureDefinitionNodeGenerator::ClosureDefinitionNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST ClosureDefinitionNodeGenerator::Parse() {
            if (L.LastToken != (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"closure", 0, 0}) {
                return {};
            }
            L.Scan();

            AST OuterVars = ArgumentsNodeGenerator(L).Parse();
            if (OuterVars.IsNotMatchNode())
                MakeException(L"ClosureDefinitionNodeGenerator: InvalidSyntax -> Expected an ArgumentsNode");
            for (auto &I: OuterVars.Subtrees)
                if (I.Type != AST::TreeType::Identifier)
                    MakeException(
                            L"ClosureDefinitionNodeGenerator: InvalidSyntax -> Expected an identifier for param");
            
            if (L.LastToken.Kind != Lexer::TokenKind::ToSign)
                MakeException(L"ClosureDefinitionNodeGenerator: InvalidSyntax -> Expected an `->`");
            L.Scan();
            
            AST Arguments = ArgumentsNodeGenerator(L).Parse();
            if (Arguments.IsNotMatchNode())
                MakeException(L"ClosureDefinitionNodeGenerator: InvalidSyntax -> Expected an ArgumentsNode");
            for (auto &I: Arguments.Subtrees)
                if (I.Type != AST::TreeType::Identifier)
                    MakeException(
                            L"ClosureDefinitionNodeGenerator: InvalidSyntax -> Expected an identifier for param");

            AST CodeBlock = CodeBlockNodeGenerator(L).Parse();
            if (CodeBlock.IsNotMatchNode())
                MakeException(L"ClosureDefinitionNodeGenerator: InvalidSyntax -> Expected a CodeBlockNode");

            return {AST::TreeType::ClosureDefinition, {OuterVars, Arguments, CodeBlock}};
        }
    } // XScript
} // Generator