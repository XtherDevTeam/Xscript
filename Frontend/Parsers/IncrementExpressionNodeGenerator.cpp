//
// Created by Jerry Chou on 2022/5/21.
//

#include "IncrementExpressionNodeGenerator.hpp"

namespace XScript::Generator {
        IncrementExpressionNodeGenerator::IncrementExpressionNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST IncrementExpressionNodeGenerator::Parse() {
            AST Right = NegativeExpressionNodeGenerator(L).Parse();
            if (Right.IsNotMatchNode()) {
                Rollback();
                return {};
            }
            if (L.LastToken.Kind == Lexer::TokenKind::IncrementSign) {
                L.Scan();
                return {AST::TreeType::IncrementExpression, {Right}};
            }
            return Right;
        }
    } // Generator