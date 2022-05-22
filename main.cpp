#include <iostream>

/* XScript 2 Project includes */
#include "Tests/BasicTests.hpp"
#include "Frontend/Lexer.hpp"
#include "Frontend/AST.hpp"
#include "Frontend/Parsers/IndexExpressionNodeGenerator.hpp"

int main() {
    auto Test = XScript::Instance::Tests::CreateCalcTest();
    Test.Run();
    std::cout << XScript::wstring2string(Test.InterpreterEnvironment.Stack.Elements.back().ToString()) << std::endl;
    std::cout << XScript::Hash(L"Hello, World!") << std::endl;

    /* AST Test */
    XScript::XString Str = L"a[1][2]";
    XScript::Lexer Lex{Str};
    Lex.Scan();
    XScript::AST Tree{XScript::Generator::IndexExpressionNodeGenerator{Lex}.Parse()};

    return 0;
}
