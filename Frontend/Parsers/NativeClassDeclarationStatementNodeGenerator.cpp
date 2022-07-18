//
// Created by Jerry Chou on 22-7-18.
//

#include "NativeClassDeclarationStatementNodeGenerator.hpp"

namespace XScript {
    Generator::NativeClassDeclarationStatementNodeGenerator::NativeClassDeclarationStatementNodeGenerator(Lexer &L)
            : BaseGenerator(L) {

    }

    AST Generator::NativeClassDeclarationStatementNodeGenerator::Parse() {
        if (L.LastToken == (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"native_class", 0, 0}) {
            L.Scan();
            if (L.LastToken.Kind != Lexer::TokenKind::Identifier) {
                MakeException(L"NativeClassDeclarationStatementNodeGenerator::Parse(): Expected an identifier");
            }
            AST Identifier = {AST::TreeType::Identifier, L.LastToken};
            L.Scan();

            if (L.LastToken != (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"in", 0, 0}) {
                MakeException(L"NativeClassDeclarationStatementNodeGenerator::Parse(): Expected `in`");
            }
            L.Scan();

            if (L.LastToken.Kind != Lexer::TokenKind::String) {
                MakeException(L"NativeClassDeclarationStatementNodeGenerator::Parse(): Expected a string");
            }
            AST Str = {AST::TreeType::Primary, L.LastToken};
            L.Scan();

            return {AST::TreeType::NativeClassDeclarationStatement, {Identifier, Str}};
        }
        return {};
    }
} // XScript