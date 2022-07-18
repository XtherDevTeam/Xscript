//
// Created by Jerry Chou on 2022/5/29.
//

#include "FileStatementNodeGenerator.hpp"
#include "FunctionDefinitionNodeGenerator.hpp"
#include "VariableStatementNodeGenerator.hpp"
#include "ClassDefinitionNodeGenerator.hpp"
#include "ImportStatementNodeGenerator.hpp"
#include "PackageStatementNodeGenerator.hpp"
#include "NativeClassDeclarationStatementNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        FileStatementNodeGenerator::FileStatementNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST FileStatementNodeGenerator::Parse() {
            AST Result{};

            Result = NativeClassDeclarationStatementNodeGenerator(L).Parse();
            if (!Result.IsNotMatchNode())
                return Result;

            Result = ImportStatementNodeGenerator(L).Parse();
            if (!Result.IsNotMatchNode())
                return Result;

            Result = PackageStatementNodeGenerator(L).Parse();
            if (!Result.IsNotMatchNode())
                return Result;

            Result = ClassDefinitionNodeGenerator(L).Parse();
            if (!Result.IsNotMatchNode())
                return Result;

            Result = FunctionDefinitionNodeGenerator(L).Parse();
            if (!Result.IsNotMatchNode())
                return Result;

            Result = VariableStatementNodeGenerator(L).Parse();
            return Result;
        }
    } // XScript
} // Generator