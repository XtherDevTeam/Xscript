//
// Created by Jerry Chou on 2022/5/24.
//

#include "StatementNodeGenerator.hpp"
#include "VariableStatementNodeGenerator.hpp"
#include "IfStatementNodeGenerator.hpp"
#include "ExpressionNodeGenerator.hpp"
#include "CodeBlockNodeGenerator.hpp"
#include "WhileStatementNodeGenerator.hpp"
#include "ForStatementNodeGenerator.hpp"
#include "BreakStatementNodeGenerator.hpp"
#include "ContinueStatementNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        StatementNodeGenerator::StatementNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST StatementNodeGenerator::Parse() {
            AST Result{};
            Result = VariableStatementNodeGenerator(L).Parse();
            if (!Result.IsNotMatchNode())
                return Result;

            Result = IfStatementNodeGenerator(L).Parse();
            if (!Result.IsNotMatchNode())
                return Result;

            Result = WhileStatementNodeGenerator(L).Parse();
            if (!Result.IsNotMatchNode())
                return Result;

            Result = ForStatementNodeGenerator(L).Parse();
            if (!Result.IsNotMatchNode())
                return Result;

            Result = BreakStatementNodeGenerator(L).Parse();
            if (!Result.IsNotMatchNode())
                return Result;

            Result = ContinueStatementNodeGenerator(L).Parse();
            if (!Result.IsNotMatchNode())
                return Result;

            Result = CodeBlockNodeGenerator(L).Parse();
            if (!Result.IsNotMatchNode())
                return Result;

            Result = ExpressionNodeGenerator(L).Parse();
            if (!Result.IsNotMatchNode())
                return Result;

            return Result;
        }
    } // XScript
} // Generator