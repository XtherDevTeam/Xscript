//
// Created by p0010 on 22-8-12.
//

#include "AliasStatementNodeGenerator.h"

namespace XScript {
    namespace Generator {
        AST AliasStatementNodeGenerator::Parse() {
            if (L.LastToken == (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"alias", 0, 0}) {
                Lexer::Token Tok = L.Scan();
                if (Tok.Kind != Lexer::TokenKind::Identifier) {
                    MakeException(L"AliasStatementNodeGenerator: Expected a identifier for package alias.");
                }
                return {AST::TreeType::AliasStatement, Tok};
            } else {
                return {};
            }
        }
    } // XScript
} // Generator