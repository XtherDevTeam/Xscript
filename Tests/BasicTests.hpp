//
// Created by Jerry Chou on 2022/5/20.
//

#ifndef XSCRIPT2_BASICTESTS_HPP
#define XSCRIPT2_BASICTESTS_HPP

#include "BasicTestFramework.hpp"

namespace XScript::Instance::Tests {

    XScript::Instance::BasicTestFramework CreateCalcTest();

    XScript::Instance::BasicTestFramework CreateCustomTest(XArray<BytecodeStructure> Commands);
} // Tests

#endif //XSCRIPT2_BASICTESTS_HPP