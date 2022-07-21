//
// Created by chou on 22-7-20.
//

#include "TryCatchStatementNodeGenerator.hpp"
#include "CodeBlockNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        TryCatchStatementNodeGenerator::TryCatchStatementNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST TryCatchStatementNodeGenerator::Parse() {
            if (L.LastToken != (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"try", 0, 0}) {
                return {};
            }
            L.Scan();
            AST TryBlock = CodeBlockNodeGenerator(L).Parse();
            if (TryBlock.IsNotMatchNode())
                MakeException(L"TryCatchStatementNodeGenerator::Parse(): Expected a code block");
            if (L.LastToken != (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"catch", 0, 0})
                MakeException(L"TryCatchStatementNodeGenerator::Parse(): Expected `catch`");
            L.Scan();
            if (L.LastToken != (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"as", 0, 0})
                MakeException(L"TryCatchStatementNodeGenerator::Parse(): Expected `as`");
            L.Scan();

            if (L.LastToken.Kind != Lexer::TokenKind::Identifier)
                MakeException(L"TryCatchStatementNodeGenerator::Parse(): Expected an identifier");
            AST Ident = {AST::TreeType::Identifier, L.LastToken};
            L.Scan();

            AST CatchBlock = CodeBlockNodeGenerator(L).Parse();

            return {AST::TreeType::TryCatchStatement, {TryBlock, Ident, CatchBlock}};
        }
    } // XScript
} // Generator