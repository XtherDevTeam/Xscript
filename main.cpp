#include <iostream>

/* XScript 2 Project includes */
#include "Tests/BasicTests.hpp"
#include "Frontend/Lexer.hpp"
#include "Frontend/AST.hpp"
#include "Backend/Compiler/ExpressionCompiler.hpp"
#include "Frontend/Parsers/StatementNodeGenerator.hpp"
#include "Backend/Compiler/StatementCompiler.hpp"

int main() {
    /* AST Test */
    XScript::XString Str = L"if (True) { var i = 0; };";
    XScript::Lexer Lex{Str};
    Lex.Scan();
    XScript::AST Tree{};
    try { Tree = {XScript::Generator::StatementNodeGenerator{Lex}.Parse()}; } catch (XScript::ParserException &E) {
        std::cout << E.what() << "wdnmd\n";
    }

    /* Compiler Test */
    XScript::Compiler::CompilerEnvironment Environment{};
    XScript::Compiler::StatementCompiler Compiler{Environment};
    auto Result = Compiler.Generate(Tree);
    for (auto &I: Result) {
        std::cout << XScript::wstring2string(I.ToString()) << std::endl;
    }

    auto Test = XScript::Instance::Tests::CreateCustomTest(Result);
    Test.Run();
    std::cout << XScript::wstring2string(Test.InterpreterEnvironment.Stack.Elements.back().ToString()) << std::endl;
    return 0;
}
