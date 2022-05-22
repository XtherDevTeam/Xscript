//
// Created by Jerry Chou on 2022/5/13.
//

#ifndef XSCRIPT2_BYTECODESTRUCTURE_HPP
#define XSCRIPT2_BYTECODESTRUCTURE_HPP

#include "../Share/Utils.hpp"

namespace XScript {

    class BytecodeStructure {
    public:
        union InstructionParam {
            explicit InstructionParam(XInteger intValue);

            explicit InstructionParam(XDecimal deciValue);

            explicit InstructionParam(XBoolean boolValue);

            explicit InstructionParam(XHeapIndexType heapPointerValue);

            XInteger IntValue;
            XDecimal DeciValue;
            XBoolean BoolValue;
            XHeapIndexType HeapPointerValue;
        };

        enum class InstructionEnum : XInteger {
            calculation_add,
            calculation_sub,
            calculation_mul,
            calculation_div,
            calculation_mod,
            calculation_negate,
            calculation_increment,
            calculation_decrement,
            logic_and,
            logic_or,
            logic_equal,
            logic_not_equal,
            logic_great_equal,
            logic_less_equal,
            logic_great,
            logic_less,
            binary_and,
            binary_or,
            binary_xor,
            binary_not,
            binary_lm,
            binary_rm,
            stack_push_integer,
            stack_push_decimal,
            stack_push_boolean,
            stack_push_empty,
            stack_pop,
            stack_duplicate,
            stack_store,
            constants_load,
            class_new,
            class_get_member,
            list_new,
            list_get_member,
            list_remove_index,
            list_push,
            list_pop,
            object_lvalue2rvalue
        } Instruction;

        InstructionParam Param;

        BytecodeStructure(BytecodeStructure::InstructionEnum instruction, InstructionParam param);
    };
} // XScript

#endif //XSCRIPT2_BYTECODESTRUCTURE_HPP
