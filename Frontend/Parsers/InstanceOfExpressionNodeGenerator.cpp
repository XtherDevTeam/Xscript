//
// Created by XIaokang00010 on 2022/7/24.
//

#include "InstanceOfExpressionNodeGenerator.hpp"
#include "AdditionExpressionNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        InstanceOfExpressionNodeGenerator::InstanceOfExpressionNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST InstanceOfExpressionNodeGenerator::Parse() {
            AST Left = AdditionExpressionNodeGenerator(L).Parse();
            if (L.LastToken != (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"instanceOf", 0, 0}) {
                return Left;
            }
            L.Scan();
            AST Right = IdentifierNodeGenerator(L).Parse();
            if (Right.IsNotMatchNode()) {
                MakeException(L"InstanceOfExpressionNodeGenerator::Parse(): Expected an identifier");
            }
            return {AST::TreeType::InstanceOfExpression, {Left, Right}};
        }
    } // XScript
} // Generator