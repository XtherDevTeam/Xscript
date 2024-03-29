//
// Created by Jerry Chou on 2022/5/21.
//

#include "MultiplicationExpressionNodeGenerator.hpp"

namespace XScript::Generator {
    MultiplicationExpressionNodeGenerator::MultiplicationExpressionNodeGenerator(Lexer &L) : BaseGenerator(L) {

    }

    AST MultiplicationExpressionNodeGenerator::Parse() {
        AST LeftTree = IncrementExpressionNodeGenerator(L).Parse();
        if (LeftTree.IsNotMatchNode()) {
            if ((LeftTree = DecrementExpressionNodeGenerator(L).Parse()).IsNotMatchNode()) {
                Rollback();
                return {};
            }
        }
        while (L.LastToken.Kind == Lexer::TokenKind::Asterisk or L.LastToken.Kind == Lexer::TokenKind::Slash or
               L.LastToken.Kind == Lexer::TokenKind::PercentSign) {
            AST Operator = {AST::TreeType::Operator, L.LastToken};
            L.Scan();
            AST RightTree = IncrementExpressionNodeGenerator(L).Parse();
            if (RightTree.IsNotMatchNode()) {
                if ((LeftTree = DecrementExpressionNodeGenerator(L).Parse()).IsNotMatchNode()) {
                    Rollback();
                    return {};
                }
                MakeException(L"MultiplicationExpressionNodeGenerator: Expected a right hand side");
            }
            LeftTree = {AST::TreeType::AdditionExpression, {LeftTree, Operator, RightTree}};
        }
        return LeftTree;
    }
} // Generator