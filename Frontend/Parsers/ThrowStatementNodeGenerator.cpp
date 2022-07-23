//
// Created by XIaokang00010 on 2022/7/23.
//

#include "ThrowStatementNodeGenerator.hpp"
#include "ExpressionNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        ThrowStatementNodeGenerator::ThrowStatementNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST ThrowStatementNodeGenerator::Parse() {
            if (L.LastToken == (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"throw", 0, 0}) {
                L.Scan();
                AST Expression = ExpressionNodeGenerator(L).Parse();
                if (Expression.IsNotMatchNode())
                    MakeException(L"ThrowStatementNodeGenerator::Parse(): Expected a expression");

                return {AST::TreeType::ThrowStatement, {Expression}};
            } else {
                return {};
        }
    }
} // XScript
} // Generator