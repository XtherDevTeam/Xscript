//
// Created by Jerry Chou on 2022/5/21.
//

#include "ExpressionNodeGenerator.hpp"

namespace XScript::Generator {
    ExpressionNodeGenerator::ExpressionNodeGenerator(Lexer &L) : BaseGenerator(L) {

    }

    AST ExpressionNodeGenerator::Parse() {
        AST Result = AssignmentExpressionNodeGenerator(L).Parse();
        if (Result.IsNotMatchNode()) {
            Result = LogicExpressionNodeGenerator(L).Parse();
            return Result;
        }
        return Result;
    }
} // Generator