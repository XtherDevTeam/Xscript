//
// Created by Jerry Chou on 2022/5/21.
//

#include "DecrementExpressionNodeGenerator.hpp"

namespace XScript::Generator {
    DecrementExpressionNodeGenerator::DecrementExpressionNodeGenerator(Lexer &L) : BaseGenerator(L) {

    }

    AST DecrementExpressionNodeGenerator::Parse() {
        AST Right = NegativeExpressionNodeGenerator(L).Parse();
        if (Right.IsNotMatchNode()) {
            Rollback();
            return {};
        }
        if (L.LastToken.Kind == Lexer::TokenKind::DecrementSign) {
            L.Scan();
            return {AST::TreeType::DecrementExpression, {Right}};
        }
        return Right;
    }
} // Generator