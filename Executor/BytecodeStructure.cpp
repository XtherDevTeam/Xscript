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

    BytecodeStructure::BytecodeStructure(BytecodeStructure::InstructionEnum instruction, InstructionParam param)
            : Instruction(instruction), Param(param) {}

    XString BytecodeStructure::ToString() const {
        XString Result;
        XInteger ParamType;
        constexpr XInteger N = 0, I = 1, D = 2, B = 3, H = 4;
        switch (Instruction) {
            case InstructionEnum::calculation_add:
                Result += L"calculation_add";
                ParamType = N;
                break;
            case InstructionEnum::calculation_sub:
                Result += L"calculation_sub";
                ParamType = N;
                break;
            case InstructionEnum::calculation_mul:
                Result += L"calculation_mul";
                ParamType = N;
                break;
            case InstructionEnum::calculation_div:
                Result += L"calculation_div";
                ParamType = N;
                break;
            case InstructionEnum::calculation_mod:
                Result += L"calculation_mod";
                ParamType = N;
                break;
            case InstructionEnum::calculation_negate:
                Result += L"calculation_negate";
                ParamType = N;
                break;
            case InstructionEnum::logic_and:
                Result += L"logic_and";
                ParamType = N;
                break;
            case InstructionEnum::logic_or:
                Result += L"logic_or";
                ParamType = N;
                break;
            case InstructionEnum::logic_equal:
                Result += L"logic_equal";
                ParamType = N;
                break;
            case InstructionEnum::logic_not_equal:
                Result += L"logic_not_equal";
                ParamType = N;
                break;
            case InstructionEnum::logic_great_equal:
                Result += L"logic_great_equal";
                ParamType = N;
                break;
            case InstructionEnum::logic_less_equal:
                Result += L"logic_less_equal";
                ParamType = N;
                break;
            case InstructionEnum::logic_great:
                Result += L"logic_great";
                ParamType = N;
                break;
            case InstructionEnum::logic_less:
                Result += L"logic_less";
                ParamType = N;
                break;
            case InstructionEnum::binary_and:
                Result += L"binary_and";
                ParamType = N;
                break;
            case InstructionEnum::binary_or:
                Result += L"binary_or";
                ParamType = N;
                break;
            case InstructionEnum::binary_xor:
                Result += L"binary_xor";
                ParamType = N;
                break;
            case InstructionEnum::binary_not:
                Result += L"binary_not";
                ParamType = N;
                break;
            case InstructionEnum::binary_lm:
                Result += L"binary_lm";
                ParamType = N;
                break;
            case InstructionEnum::binary_rm:
                Result += L"binary_rm";
                ParamType = N;
                break;
            case InstructionEnum::stack_push_integer:
                Result += L"stack_push_integer";
                ParamType = I;
                break;
            case InstructionEnum::stack_push_decimal:
                Result += L"stack_push_decimal";
                ParamType = D;
                break;
            case InstructionEnum::stack_push_boolean:
                Result += L"stack_push_boolean";
                ParamType = B;
                break;
            case InstructionEnum::stack_push_empty:
                Result += L"stack_push_empty";
                ParamType = N;
                break;
            case InstructionEnum::stack_pop:
                Result += L"stack_pop";
                ParamType = N;
                break;
            case InstructionEnum::stack_duplicate:
                Result += L"stack_duplicate";
                ParamType = H;
                break;
            case InstructionEnum::stack_store:
                Result += L"stack_store";
                ParamType = H;
                break;
            case InstructionEnum::constants_load:
                Result += L"constants_load";
                ParamType = H;
                break;
            case InstructionEnum::class_new:
                Result += L"class_new";
                ParamType = H;
                break;
            case InstructionEnum::class_get_member:
                Result += L"class_get_member";
                ParamType = H;
                break;
            case InstructionEnum::list_new:
                Result += L"list_new";
                ParamType = H;
                break;
            case InstructionEnum::list_get_member:
                Result += L"list_get_member";
                ParamType = N;
                break;
            case InstructionEnum::list_remove_index:
                Result += L"list_remove_index";
                ParamType = N;
                break;
            case InstructionEnum::list_push:
                Result += L"list_push";
                ParamType = N;
                break;
            case InstructionEnum::list_pop:
                Result += L"list_pop";
                ParamType = N;
                break;
            case InstructionEnum::pc_jump_if_true:
                Result += L"pc_jump_if_true";
                ParamType = I;
                break;
            case InstructionEnum::pc_jump_if_false:
                Result += L"pc_jump_if_false";
                ParamType = I;
                break;
            case InstructionEnum::pc_jump:
                Result += L"pc_jump";
                ParamType = I;
                break;
            case InstructionEnum::debugger:
                Result += L"debugger";
                ParamType = H;
                break;
            case InstructionEnum::static_get:
                Result += L"static_get";
                ParamType = H;
                break;
            case InstructionEnum::static_store:
                Result += L"static_store";
                ParamType = H;
                break;
            case InstructionEnum::object_lvalue2rvalue:
                Result += L"object_lvalue2rvalue";
                ParamType = N;
                break;
            case InstructionEnum::object_store:
                Result += L"object_store";
                ParamType = N;
                break;
            case InstructionEnum::fake_command_continue:
            case InstructionEnum::fake_command_break:
                /* dummy branch */
                ParamType = N;
                break;
            case InstructionEnum::func_invoke:
                Result += L"func_invoke";
                ParamType = H;
                break;
            case InstructionEnum::func_return:
                Result += L"func_return";
                ParamType = N;
                break;
        }

        Result = L"<XCommand Instruction=" + Result;
        switch (ParamType) {
            case N:
                Result += L" Param=None>";
                break;
            case I:
                Result += L" Param=" + std::to_wstring(Param.IntValue) + L">";
                break;
            case D:
                Result += L" Param=" + std::to_wstring(Param.DeciValue) + L">";
                break;
            case B: {
                XString Temp = Param.BoolValue ? L"True" : L"False";
                Result += L" Param=" + Temp + L">";
                break;
            }
            case H:
                Result += L" Param=" + std::to_wstring(Param.HeapPointerValue) + L">";
                break;
            default:
                break;
        }
        return Result;
    }

    bool BytecodeStructure::operator==(const BytecodeStructure &rhs) const {
        return (Instruction == rhs.Instruction and Param.HeapPointerValue == rhs.Param.HeapPointerValue);
    }

    bool BytecodeStructure::operator!=(const BytecodeStructure &rhs) const {
        return (Instruction != rhs.Instruction or Param.HeapPointerValue != rhs.Param.HeapPointerValue);
    }

    BytecodeStructure &BytecodeStructure::operator=(const BytecodeStructure &rhs) {
        Instruction = rhs.Instruction;
        Param.HeapPointerValue = rhs.Param.HeapPointerValue;
        return *this;
    }

    BytecodeStructure::BytecodeStructure() : Instruction(), Param(static_cast<XIndexType>(0)) {

    }
} // XScript