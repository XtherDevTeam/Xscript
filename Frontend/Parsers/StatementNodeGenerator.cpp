//
// Created by Jerry Chou on 2022/5/24.
//

#include "StatementNodeGenerator.hpp"
#include "VariableStatementNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        StatementNodeGenerator::StatementNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST StatementNodeGenerator::Parse() {
            AST Result{};
            Result = VariableStatementNodeGenerator(L).Parse();
            if (!Result.IsNotMatchNode())
                return Result;

            return Result;
        }
    } // XScript
} // Generator