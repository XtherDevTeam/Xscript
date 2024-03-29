//
// Created by Jerry Chou on 2022/5/21.
//

#include "NegativeExpressionNodeGenerator.hpp"
#include "NewExpressionNodeGenerator.hpp"
#include "UnnamedFunctionDefinitionNodeGenerator.hpp"
#include "ClosureDefinitionNodeGenerator.hpp"

namespace XScript::Generator {
    NegativeExpressionNodeGenerator::NegativeExpressionNodeGenerator(Lexer &L) : BaseGenerator(L) {
    }

    AST NegativeExpressionNodeGenerator::Parse() {
        if (L.LastToken.Kind == Lexer::TokenKind::Minus) {
            L.Scan();
            AST Right = MemberExpressionNodeGenerator(L).Parse();
            if (Right.IsNotMatchNode()) {
                Right = NewExpressionNodeGenerator(L).Parse();
                if (Right.IsNotMatchNode()) {
                    Right = UnnamedFunctionDefinitionNodeGenerator(L).Parse();
                    if (Right.IsNotMatchNode()) {
                        Right = ClosureDefinitionNodeGenerator(L).Parse();
                        if (Right.IsNotMatchNode()) {
                            Right = PrimaryNodeGenerator(L).Parse();
                            if (Right.IsNotMatchNode()) {
                                MakeException(L"Expected a rvalue expression.");
                            }
                        }
                    }
                }
            }
            return {AST::TreeType::NegativeExpression, {Right}};
        }
        AST Right = MemberExpressionNodeGenerator(L).Parse();
        if (Right.IsNotMatchNode()) {
            Right = NewExpressionNodeGenerator(L).Parse();
            if (Right.IsNotMatchNode()) {
                Right = UnnamedFunctionDefinitionNodeGenerator(L).Parse();
                if (Right.IsNotMatchNode()) {
                    Right = ClosureDefinitionNodeGenerator(L).Parse();
                    if (Right.IsNotMatchNode()) {
                        return PrimaryNodeGenerator(L).Parse();
                    }
                }
            }
        }
        return Right;
    }
} // Generator