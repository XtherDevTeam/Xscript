//
// Created by p0010 on 22-8-12.
//

#include "AliasStatementNodeGenerator.hpp"

namespace XScript::Generator {
    AST AliasStatementNodeGenerator::Parse() {
        if (L.LastToken == (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"alias", 0, 0}) {
            Lexer::Token Tok = L.Scan();
            if (Tok.Kind != Lexer::TokenKind::Identifier) {
                MakeException(L"AliasStatementNodeGenerator: Expected a identifier for package alias.");
            }
            L.Scan();
            return {AST::TreeType::AliasStatement, Tok};
        } else {
            return {};
        }
    }

    AliasStatementNodeGenerator::AliasStatementNodeGenerator(Lexer &L) : BaseGenerator(L) {

    }
} // Generator