//
// Created by Jerry Chou on 2022/6/18.
//

#include "PackageStatementNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        PackageStatementNodeGenerator::PackageStatementNodeGenerator(Lexer &L) : BaseGenerator(L) {
        }

        AST PackageStatementNodeGenerator::Parse() {
            if (L.LastToken == (Lexer::Token){Lexer::TokenKind::ReservedWords, L"package", 0, 0}) {
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