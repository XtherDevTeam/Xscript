//
// Created by Jerry Chou on 2022/5/28.
//

#include "ContinueStatementNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        ContinueStatementNodeGenerator::ContinueStatementNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST ContinueStatementNodeGenerator::Parse() {
            if (L.LastToken == (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"continue", 0, 0}) {
                L.Scan();
                return {AST::TreeType::ContinueStatement, (Lexer::Token) {}};
            }
            Rollback();
            return {};
        }
    } // XScript
} // Generator