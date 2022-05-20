#include <iostream>

/* XScript 2 Project includes */
#include "Tests/BasicTests.hpp"

int main() {
    auto Test = XScript::Instance::Tests::CreateCalcTest();
    Test.Run();
    std::cout << XScript::wstring2string(Test.InterpreterEnvironment.Stack.Elements.back().ToString()) << std::endl;
    return 0;
}
