//
// Created by Jerry Chou on 2022/5/28.
//

#include "BreakStatementNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        BreakStatementNodeGenerator::BreakStatementNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST BreakStatementNodeGenerator::Parse() {
            if (L.LastToken == (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"break", 0, 0}) {
                L.Scan();
                return {AST::TreeType::BreakStatement, (Lexer::Token) {}};
            }
            Rollback();
            return {};
        }
    } // XScript
} // Generator