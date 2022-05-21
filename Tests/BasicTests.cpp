//
// Created by Jerry Chou on 2022/5/20.
//

#include "BasicTests.hpp"

namespace XScript::Instance::Tests {
    XScript::Instance::BasicTestFramework CreateCalcTest() {
        XScript::Instance::BasicTestFramework Result;
        Result.Commands = XArray<BytecodeStructure>{
                (BytecodeStructure) {BytecodeStructure::InstructionEnum::stack_push_integer,
                                     (BytecodeStructure::InstructionParam) {(XInteger) 1}},
                (BytecodeStructure) {BytecodeStructure::InstructionEnum::stack_push_decimal,
                                     (BytecodeStructure::InstructionParam) {(XDecimal) 2}},
                (BytecodeStructure) {BytecodeStructure::InstructionEnum::calculation_add,
                                     (BytecodeStructure::InstructionParam) {(XIndexType) 0}},
        };
        return Result;
    }
} // Tests