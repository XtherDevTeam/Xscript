//
// Created by Jerry Chou on 2022/5/21.
//

#include "IdentifierNodeGenerator.hpp"
#include "CrossPackageAccessExpressionNodeGenerator.hpp"

namespace XScript::Generator {
    IdentifierNodeGenerator::IdentifierNodeGenerator(Lexer &L) : BaseGenerator(L) {

    }

    AST IdentifierNodeGenerator::Parse() {
        if (L.LastToken.Kind == Lexer::TokenKind::Identifier) {
            AST Result{AST::TreeType::Identifier, L.LastToken};
            L.Scan();   // prepare for next-time's read.
            return Result;
        } else {
            AST Result = CrossPackageAccessExpressionNodeGenerator(L).Parse();
            if (!Result.IsNotMatchNode())
                return Result;
        }
        Rollback(); // rollback to initial state.
        return {};
    }
} // Generator