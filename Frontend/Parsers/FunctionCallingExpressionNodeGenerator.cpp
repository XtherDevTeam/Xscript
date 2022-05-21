//
// Created by Jerry Chou on 2022/5/21.
//

#include "FunctionCallingExpressionNodeGenerator.hpp"

namespace XScript::Generator {
        FunctionCallingExpressionNodeGenerator::FunctionCallingExpressionNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST FunctionCallingExpressionNodeGenerator::Parse( ) {
            AST Result{};
            AST First = IndexExpressionNodeGenerator(L).Parse();
            if (First.IsNotMatchNode()) {
                Rollback();
                return {};
            }

            AST Arguments = ArgumentsNodeGenerator(L).Parse();
            if (Arguments.IsNotMatchNode()) {
                return First;
            }
            Result = {AST::TreeType::FunctionCallingExpression, {First, Arguments}};
            return Result;
        }
    } // Generator