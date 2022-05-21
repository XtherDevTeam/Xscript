//
// Created by Jerry Chou on 2022/5/21.
//

#include "MemberExpressionNodeGenerator.hpp"

namespace XScript::Generator {
        MemberExpressionNodeGenerator::MemberExpressionNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST MemberExpressionNodeGenerator::Parse() {
            AST Result{};
            Result = FunctionCallingExpressionNodeGenerator(L).Parse();
            if (L.LastToken.Kind != Lexer::TokenKind::Dot) {
                return Result;
            }
            L.Scan();

            while (true) {
                AST Temp = FunctionCallingExpressionNodeGenerator(L).Parse();
                if (Temp.IsNotMatchNode()) break;
                Result = {AST::TreeType::MemberExpression, {Result, Temp}};
                if (L.LastToken.Kind != Lexer::TokenKind::Dot) {
                    break;
                }
                L.Scan();
            }
            return Result;
        }
    } // Generator