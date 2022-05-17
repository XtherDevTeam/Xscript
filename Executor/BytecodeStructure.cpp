//
// Created by Jerry Chou on 2022/5/13.
//

#include "BytecodeStructure.hpp"

namespace XScript {
    BytecodeStructure::InstructionParam::InstructionParam(XInteger intValue) : IntValue(intValue) {}

    BytecodeStructure::InstructionParam::InstructionParam(XDecimal deciValue) : DeciValue(deciValue) {}

    BytecodeStructure::InstructionParam::InstructionParam(XBoolean boolValue) : BoolValue(boolValue) {}

    BytecodeStructure::InstructionParam::InstructionParam(XHeapIndexType heapPointerValue) : HeapPointerValue(
            heapPointerValue) {}
} // XScript