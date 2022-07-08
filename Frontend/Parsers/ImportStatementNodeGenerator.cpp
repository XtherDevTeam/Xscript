//
// Created by Jerry Chou on 2022/6/18.
//

#include "ImportStatementNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        ImportStatementNodeGenerator::ImportStatementNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST ImportStatementNodeGenerator::Parse() {
            if (L.LastToken == (Lexer::Token){Lexer::TokenKind::ReservedWords, L"import", 0, 0}) {
                L.Scan();
                AST R{AST::TreeType::ImportStatement, L.LastToken};
                L.Scan();
                return R;
            }
            Rollback();
            return {};
        }
    } // XScript
} // Generator