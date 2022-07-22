//
// Created by Jerry Chou on 2022/5/14.
//

#include "BytecodeInterpreter.hpp"

namespace XScript {
    BytecodeInterpreter::BytecodeInterpreter(Environment &interpreterEnvironment, GarbageCollection &GC) :
            InterpreterEnvironment(interpreterEnvironment), GC(GC) {}

    void BytecodeInterpreter::MainLoop() {
        while (InterpreterEnvironment.ProgramCounter.NowIndex !=
               InterpreterEnvironment.ProgramCounter.Pointer->size()) {
            auto &CurrentInstruction = (*InterpreterEnvironment.ProgramCounter.Pointer)[InterpreterEnvironment.ProgramCounter.NowIndex];

            switch (CurrentInstruction.Instruction) {
                case BytecodeStructure::InstructionEnum::calculation_add:
                    InstructionCalculationAdd(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::calculation_sub:
                    InstructionCalculationSub(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::calculation_mul:
                    InstructionCalculationMul(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::calculation_div:
                    InstructionCalculationDiv(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::calculation_mod:
                    InstructionCalculationMod(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::calculation_negate:
                    InstructionCalculationNegate(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::logic_and:
                    InstructionLogicAnd(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::logic_or:
                    InstructionLogicOr(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::logic_equal:
                    InstructionLogicEqual(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::logic_not_equal:
                    InstructionLogicNotEqual(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::logic_great_equal:
                    InstructionLogicGreatEqual(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::logic_less_equal:
                    InstructionLogicLessEqual(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::logic_great:
                    InstructionLogicGreat(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::logic_less:
                    InstructionLogicLess(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::binary_and:
                    InstructionBinaryAnd(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::binary_or:
                    InstructionBinaryOr(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::binary_xor:
                    InstructionBinaryXOR(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::binary_not:
                    InstructionBinaryNot(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::binary_lm:
                    InstructionBinaryLM(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::binary_rm:
                    InstructionBinaryRM(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::stack_push_integer:
                    InstructionStackPushInteger(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::stack_push_decimal:
                    InstructionStackPushDecimal(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::stack_push_boolean:
                    InstructionStackPushBoolean(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::stack_push_function:
                    InstructionStackPushFunction(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::stack_push_empty:
                    InstructionStackPushEmpty(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::stack_pop:
                    InstructionStackPop(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::stack_duplicate:
                    InstructionStackDuplicate(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::stack_get_top:
                    InstructionStackGetTop(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::stack_store:
                    InstructionStackStore(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::constants_load:
                    InstructionConstantsLoad(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::class_new:
                    InstructionClassNew(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::class_get_member:
                    InstructionClassGetMember(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::class_new_member:
                    InstructionClassNewMember(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::list_new:
                    InstructionListNew(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::list_get_member:
                    InstructionListGetMember(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::list_remove_index:
                    InstructionListRemoveIndex(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::list_push:
                    InstructionListPush(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::list_pop:
                    InstructionListPop(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::pc_jump_if_true:
                    InstructionPCJumpIfTrue(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::pc_jump_if_false:
                    InstructionPCJumpIfFalse(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::pc_jump:
                    InstructionPCJump(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::pc_get_current_package_id:
                    InstructionPCGetCurrentPackageID(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::pc_set_current_package_id:
                    InstructionPCSetCurrentPackageID(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::pc_restore_package_id:
                    InstructionPCRestorePackageID(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::debugger:
                    break;
                case BytecodeStructure::InstructionEnum::static_store:
                    InstructionStaticStore(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::static_get:
                    InstructionStaticGet(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::object_lvalue2rvalue:
                    InstructionObjectLvalue2Rvalue(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::object_store:
                    InstructionObjectStore(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::func_invoke:
                    InstructionFuncInvoke(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::func_return:
                    InstructionFuncReturn(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::native_class_new:
                    InstructionNativeClassNew(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::exception_push:
                    InstructionExceptionPush(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::exception_pop:
                    InstructionExceptionPop(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::exception_throw:
                    InstructionExceptionThrow(CurrentInstruction.Param);
                    break;
                case BytecodeStructure::InstructionEnum::force_exit:
                    return;
                case BytecodeStructure::InstructionEnum::fake_command_continue:
                case BytecodeStructure::InstructionEnum::fake_command_break:
                    break;
            }
            InterpreterEnvironment.ProgramCounter.NowIndex++;
        }
    }

    void BytecodeInterpreter::InstructionCalculationAdd(BytecodeStructure::InstructionParam Param) {
        auto Right = InterpreterEnvironment.Stack.PopValueFromStack();
        auto Left = InterpreterEnvironment.Stack.PopValueFromStack();
        switch (Left.Kind) {
            case EnvironmentStackItem::ItemKind::Integer:
                switch (Right.Kind) {
                    case EnvironmentStackItem::ItemKind::Integer:
                        Left.Value.IntVal += Right.Value.IntVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Decimal:
                        Left.Value.DeciVal = static_cast<XDecimal>(Left.Value.IntVal) + Right.Value.DeciVal;
                        Left.Kind = EnvironmentStackItem::ItemKind::Decimal;
                        break;
                    case EnvironmentStackItem::ItemKind::Boolean:
                        Left.Value.IntVal += static_cast<XInteger>(Right.Value.BoolVal);
                        break;
                    case EnvironmentStackItem::ItemKind::FunctionPointer:
                    case EnvironmentStackItem::ItemKind::HeapPointer:
                        throw BytecodeInterpretError(L"Cannot add integers with a object.");
                    case EnvironmentStackItem::ItemKind::Null:
                        throw BytecodeInterpretError(L"Cannot add integers with a null value.");
                }
                InterpreterEnvironment.Stack.PushValueToStack(Left);
                break;
            case EnvironmentStackItem::ItemKind::Decimal:
                switch (Right.Kind) {
                    case EnvironmentStackItem::ItemKind::Integer:
                        Left.Value.DeciVal = Left.Value.DeciVal + static_cast<XDecimal>(Right.Value.IntVal);
                        break;
                    case EnvironmentStackItem::ItemKind::Decimal:
                        Left.Value.DeciVal += Right.Value.DeciVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Boolean:
                        Left.Value.DeciVal += static_cast<XDecimal>(Right.Value.BoolVal);
                        break;
                    case EnvironmentStackItem::ItemKind::FunctionPointer:
                    case EnvironmentStackItem::ItemKind::HeapPointer:
                        throw BytecodeInterpretError(L"Cannot add integers with a object.");
                    case EnvironmentStackItem::ItemKind::Null:
                        throw BytecodeInterpretError(L"Cannot add integers with a null value.");
                }
                InterpreterEnvironment.Stack.PushValueToStack(Left);
                break;
            case EnvironmentStackItem::ItemKind::Boolean:
                switch (Right.Kind) {
                    case EnvironmentStackItem::ItemKind::Integer:
                        Left.Value.IntVal = static_cast<XInteger>(Left.Value.BoolVal) + Right.Value.IntVal;
                        Left.Kind = EnvironmentStackItem::ItemKind::Integer;
                        break;
                    case EnvironmentStackItem::ItemKind::Decimal:
                        Left.Value.DeciVal =
                                static_cast<XDecimal>(Left.Value.BoolVal) + Right.Value.DeciVal;
                        Left.Kind = EnvironmentStackItem::ItemKind::Decimal;
                        break;
                    case EnvironmentStackItem::ItemKind::Boolean:
                        Left.Value.BoolVal += Right.Value.BoolVal;
                        break;
                    case EnvironmentStackItem::ItemKind::FunctionPointer:
                    case EnvironmentStackItem::ItemKind::HeapPointer:
                        throw BytecodeInterpretError(L"Cannot add integers with a object.");
                    case EnvironmentStackItem::ItemKind::Null:
                        throw BytecodeInterpretError(L"Cannot add integers with a null value.");
                }
                InterpreterEnvironment.Stack.PushValueToStack(Left);
                break;
            case EnvironmentStackItem::ItemKind::HeapPointer:
                switch (InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal].Kind) {
                    case EnvObject::ObjectKind::ClassObject: {
                        auto &ClassObject = *InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal].Value.ClassObjectPointer;
                        auto &Method = InterpreterEnvironment.Heap.HeapData[ClassObject.GetMember(
                                Hash(L"__instruction_add__"))];
                        if (Method.Kind == EnvObject::ObjectKind::FunctionPointer) {
                            InterpreterEnvironment.Stack.PushValueToStack(Left); // this
                            InterpreterEnvironment.Stack.PushValueToStack(Right); // rhs
                            InterpreterEnvironment.Stack.PushValueToStack(
                                    {EnvironmentStackItem::ItemKind::FunctionPointer,
                                     (EnvironmentStackItem::ItemValue) {Method.Value.FunctionPointerValue}});
                            InstructionFuncInvoke((BytecodeStructure::InstructionParam) {static_cast<XIndexType>(2)});
                        } else {
                            throw BytecodeInterpretError(L"Member `__instruction_add__` isn't a method");
                        }
                        break;
                    }
                    case EnvObject::ObjectKind::ArrayObject: {
                        break;
                    }
                    case EnvObject::ObjectKind::StringObject: {
                        if (Right.Kind == EnvironmentStackItem::ItemKind::HeapPointer and
                            InterpreterEnvironment.Heap.HeapData[Right.Value.HeapPointerVal].Kind ==
                            EnvObject::ObjectKind::StringObject) {
                            auto ObjPointer = InterpreterEnvironment.Heap.PushElement(
                                    {EnvObject::ObjectKind::StringObject,
                                     (EnvObject::ObjectValue) {MergeEnvStringObject(
                                             InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal].Value.StringObjectPointer,
                                             InterpreterEnvironment.Heap.HeapData[Right.Value.HeapPointerVal].Value.StringObjectPointer)}});

                            InterpreterEnvironment.Stack.PushValueToStack(
                                    (EnvironmentStackItem) {EnvironmentStackItem::ItemKind::HeapPointer,
                                                            (EnvironmentStackItem::ItemValue) {ObjPointer}});
                        } else {
                            throw BytecodeInterpretError(L"Unsupported string operation.");
                        }
                        break;
                    }
                    default:
                        throw BytecodeInterpretError(L"Cannot operate an basic-type heap item.");
                }
                break;
            case EnvironmentStackItem::ItemKind::FunctionPointer:
                break;
            case EnvironmentStackItem::ItemKind::Null:
                throw BytecodeInterpretError(L"Cannot add elements with a null value.");
        }
    }

    void BytecodeInterpreter::InstructionCalculationSub(BytecodeStructure::InstructionParam Param) {
        auto Right = InterpreterEnvironment.Stack.PopValueFromStack();
        auto Left = InterpreterEnvironment.Stack.PopValueFromStack();
        switch (Left.Kind) {
            case EnvironmentStackItem::ItemKind::Integer:
                switch (Right.Kind) {
                    case EnvironmentStackItem::ItemKind::Integer:
                        Left.Value.IntVal -= Right.Value.IntVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Decimal:
                        Left.Value.DeciVal = static_cast<XDecimal>(Left.Value.IntVal) - Right.Value.DeciVal;
                        Left.Kind = EnvironmentStackItem::ItemKind::Decimal;
                        break;
                    case EnvironmentStackItem::ItemKind::Boolean:
                        Left.Value.IntVal -= static_cast<XInteger>(Right.Value.BoolVal);
                        break;
                    case EnvironmentStackItem::ItemKind::FunctionPointer:
                    case EnvironmentStackItem::ItemKind::HeapPointer:
                        throw BytecodeInterpretError(L"Cannot add integers with a object.");
                    case EnvironmentStackItem::ItemKind::Null:
                        throw BytecodeInterpretError(L"Cannot add integers with a null value.");
                }
                InterpreterEnvironment.Stack.PushValueToStack(Left);
                break;
            case EnvironmentStackItem::ItemKind::Decimal:
                switch (Right.Kind) {
                    case EnvironmentStackItem::ItemKind::Integer:
                        Left.Value.DeciVal = Left.Value.DeciVal - static_cast<XDecimal>(Right.Value.IntVal);
                        break;
                    case EnvironmentStackItem::ItemKind::Decimal:
                        Left.Value.DeciVal -= Right.Value.DeciVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Boolean:
                        Left.Value.DeciVal -= static_cast<XDecimal>(Right.Value.BoolVal);
                        break;
                    case EnvironmentStackItem::ItemKind::FunctionPointer:
                    case EnvironmentStackItem::ItemKind::HeapPointer:
                        throw BytecodeInterpretError(L"Cannot add integers with a object.");
                    case EnvironmentStackItem::ItemKind::Null:
                        throw BytecodeInterpretError(L"Cannot add integers with a null value.");
                }
                InterpreterEnvironment.Stack.PushValueToStack(Left);
                break;
            case EnvironmentStackItem::ItemKind::Boolean:
                switch (Right.Kind) {
                    case EnvironmentStackItem::ItemKind::Integer:
                        Left.Value.IntVal = static_cast<XInteger>(Left.Value.BoolVal) - Right.Value.IntVal;
                        Left.Kind = EnvironmentStackItem::ItemKind::Integer;
                        break;
                    case EnvironmentStackItem::ItemKind::Decimal:
                        Left.Value.DeciVal =
                                static_cast<XDecimal>(Left.Value.BoolVal) - Right.Value.DeciVal;
                        Left.Kind = EnvironmentStackItem::ItemKind::Decimal;
                        break;
                    case EnvironmentStackItem::ItemKind::Boolean:
                        Left.Value.BoolVal -= Right.Value.BoolVal;
                        break;
                    case EnvironmentStackItem::ItemKind::HeapPointer:
                        throw BytecodeInterpretError(L"Cannot add integers with a object.");
                    case EnvironmentStackItem::ItemKind::Null:
                        throw BytecodeInterpretError(L"Cannot add integers with a null value.");
                }
                InterpreterEnvironment.Stack.PushValueToStack(Left);
                break;
            case EnvironmentStackItem::ItemKind::FunctionPointer:
                break;
            case EnvironmentStackItem::ItemKind::HeapPointer:
                switch (InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal].Kind) {
                    case EnvObject::ObjectKind::ClassObject: {
                        auto &ClassObject = *InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal].Value.ClassObjectPointer;
                        auto &Method = InterpreterEnvironment.Heap.HeapData[ClassObject.GetMember(
                                Hash(L"__instruction_sub__"))];
                        if (Method.Kind == EnvObject::ObjectKind::FunctionPointer) {
                            InterpreterEnvironment.Stack.PushValueToStack(Left); // this
                            InterpreterEnvironment.Stack.PushValueToStack(Right); // rhs
                            InterpreterEnvironment.Stack.PushValueToStack(
                                    {EnvironmentStackItem::ItemKind::FunctionPointer,
                                     (EnvironmentStackItem::ItemValue) {Method.Value.FunctionPointerValue}});
                            InstructionFuncInvoke((BytecodeStructure::InstructionParam) {static_cast<XIndexType>(2)});
                        } else {
                            throw BytecodeInterpretError(L"Member `__instruction_sub__` isn't a method");
                        }
                        break;
                    }
                    case EnvObject::ObjectKind::ArrayObject:
                        break;
                    case EnvObject::ObjectKind::StringObject:
                        throw BytecodeInterpretError(L"Unsupported string operation.");
                    default:
                        throw BytecodeInterpretError(L"Cannot operate an basic-type heap item.");
                }
                break;
            case EnvironmentStackItem::ItemKind::Null:
                throw BytecodeInterpretError(L"Cannot add elements with a null value.");
        }
    }

    void BytecodeInterpreter::InstructionCalculationMul(BytecodeStructure::InstructionParam Param) {
        auto Right = InterpreterEnvironment.Stack.PopValueFromStack();
        auto Left = InterpreterEnvironment.Stack.PopValueFromStack();
        switch (Left.Kind) {
            case EnvironmentStackItem::ItemKind::Integer:
                switch (Right.Kind) {
                    case EnvironmentStackItem::ItemKind::Integer:
                        Left.Value.IntVal *= Right.Value.IntVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Decimal:
                        Left.Value.DeciVal = static_cast<XDecimal>(Left.Value.IntVal) * Right.Value.DeciVal;
                        Left.Kind = EnvironmentStackItem::ItemKind::Decimal;
                        break;
                    case EnvironmentStackItem::ItemKind::Boolean:
                        Left.Value.IntVal *= static_cast<XInteger>(Right.Value.BoolVal);
                        break;
                    case EnvironmentStackItem::ItemKind::FunctionPointer:
                    case EnvironmentStackItem::ItemKind::HeapPointer:
                        throw BytecodeInterpretError(L"Cannot add integers with a object.");
                    case EnvironmentStackItem::ItemKind::Null:
                        throw BytecodeInterpretError(L"Cannot add integers with a null value.");
                }
                InterpreterEnvironment.Stack.PushValueToStack(Left);
                break;
            case EnvironmentStackItem::ItemKind::Decimal:
                switch (Right.Kind) {
                    case EnvironmentStackItem::ItemKind::Integer:
                        Left.Value.DeciVal = Left.Value.DeciVal * static_cast<XDecimal>(Right.Value.IntVal);
                        break;
                    case EnvironmentStackItem::ItemKind::Decimal:
                        Left.Value.DeciVal *= Right.Value.DeciVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Boolean:
                        Left.Value.DeciVal *= static_cast<XDecimal>(Right.Value.BoolVal);
                        break;
                    case EnvironmentStackItem::ItemKind::FunctionPointer:
                    case EnvironmentStackItem::ItemKind::HeapPointer:
                        throw BytecodeInterpretError(L"Cannot add integers with a object.");
                    case EnvironmentStackItem::ItemKind::Null:
                        throw BytecodeInterpretError(L"Cannot add integers with a null value.");
                }
                InterpreterEnvironment.Stack.PushValueToStack(Left);
                break;
            case EnvironmentStackItem::ItemKind::Boolean:
                switch (Right.Kind) {
                    case EnvironmentStackItem::ItemKind::Integer:
                        Left.Value.IntVal = static_cast<XInteger>(Left.Value.BoolVal) * Right.Value.IntVal;
                        Left.Kind = EnvironmentStackItem::ItemKind::Integer;
                        break;
                    case EnvironmentStackItem::ItemKind::Decimal:
                        Left.Value.DeciVal =
                                static_cast<XDecimal>(Left.Value.BoolVal) * Right.Value.DeciVal;
                        Left.Kind = EnvironmentStackItem::ItemKind::Decimal;
                        break;
                    case EnvironmentStackItem::ItemKind::Boolean:
                        Left.Value.BoolVal *= Right.Value.BoolVal;
                        break;
                    case EnvironmentStackItem::ItemKind::FunctionPointer:
                    case EnvironmentStackItem::ItemKind::HeapPointer:
                        throw BytecodeInterpretError(L"Cannot add integers with a object.");
                    case EnvironmentStackItem::ItemKind::Null:
                        throw BytecodeInterpretError(L"Cannot add integers with a null value.");
                }
                InterpreterEnvironment.Stack.PushValueToStack(Left);
                break;
            case EnvironmentStackItem::ItemKind::FunctionPointer:
                break;
            case EnvironmentStackItem::ItemKind::HeapPointer:
                switch (InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal].Kind) {
                    case EnvObject::ObjectKind::ClassObject: {
                        auto &ClassObject = *InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal].Value.ClassObjectPointer;
                        auto &Method = InterpreterEnvironment.Heap.HeapData[ClassObject.GetMember(
                                Hash(L"__instruction_mul__"))];
                        if (Method.Kind == EnvObject::ObjectKind::FunctionPointer) {
                            InterpreterEnvironment.Stack.PushValueToStack(Left); // this
                            InterpreterEnvironment.Stack.PushValueToStack(Right); // rhs
                            InterpreterEnvironment.Stack.PushValueToStack(
                                    {EnvironmentStackItem::ItemKind::FunctionPointer,
                                     (EnvironmentStackItem::ItemValue) {Method.Value.FunctionPointerValue}});
                            InstructionFuncInvoke((BytecodeStructure::InstructionParam) {static_cast<XIndexType>(2)});
                        } else {
                            throw BytecodeInterpretError(L"Member `__instruction_mul__` isn't a method");
                        }
                        break;
                    }
                    case EnvObject::ObjectKind::ArrayObject:
                        throw BytecodeInterpretError(L"Unsupported array operation.");
                        break;
                    case EnvObject::ObjectKind::StringObject:
                        throw BytecodeInterpretError(L"Unsupported string operation.");
                    default:
                        throw BytecodeInterpretError(L"Cannot operate an basic-type heap item.");
                }
                break;
            case EnvironmentStackItem::ItemKind::Null:
                throw BytecodeInterpretError(L"Cannot add elements with a null value.");
        }
    }

    void BytecodeInterpreter::InstructionCalculationDiv(BytecodeStructure::InstructionParam Param) {
        auto Right = InterpreterEnvironment.Stack.PopValueFromStack();
        auto Left = InterpreterEnvironment.Stack.PopValueFromStack();
        switch (Left.Kind) {
            case EnvironmentStackItem::ItemKind::Integer:
                switch (Right.Kind) {
                    case EnvironmentStackItem::ItemKind::Integer:
                        Left.Value.IntVal /= Right.Value.IntVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Decimal:
                        Left.Value.DeciVal = static_cast<XDecimal>(Left.Value.IntVal) / Right.Value.DeciVal;
                        Left.Kind = EnvironmentStackItem::ItemKind::Decimal;
                        break;
                    case EnvironmentStackItem::ItemKind::Boolean:
                        Left.Value.IntVal /= static_cast<XInteger>(Right.Value.BoolVal);
                        break;
                    case EnvironmentStackItem::ItemKind::FunctionPointer:
                    case EnvironmentStackItem::ItemKind::HeapPointer:
                        throw BytecodeInterpretError(L"Cannot add integers with a object.");
                    case EnvironmentStackItem::ItemKind::Null:
                        throw BytecodeInterpretError(L"Cannot add integers with a null value.");
                }
                InterpreterEnvironment.Stack.PushValueToStack(Left);
                break;
            case EnvironmentStackItem::ItemKind::Decimal:
                switch (Right.Kind) {
                    case EnvironmentStackItem::ItemKind::Integer:
                        Left.Value.DeciVal = Left.Value.DeciVal / static_cast<XDecimal>(Right.Value.IntVal);
                        break;
                    case EnvironmentStackItem::ItemKind::Decimal:
                        Left.Value.DeciVal /= Right.Value.DeciVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Boolean:
                        Left.Value.DeciVal /= static_cast<XDecimal>(Right.Value.BoolVal);
                        break;
                    case EnvironmentStackItem::ItemKind::FunctionPointer:
                    case EnvironmentStackItem::ItemKind::HeapPointer:
                        throw BytecodeInterpretError(L"Cannot add integers with a object.");
                    case EnvironmentStackItem::ItemKind::Null:
                        throw BytecodeInterpretError(L"Cannot add integers with a null value.");
                }
                InterpreterEnvironment.Stack.PushValueToStack(Left);
                break;
            case EnvironmentStackItem::ItemKind::Boolean:
                switch (Right.Kind) {
                    case EnvironmentStackItem::ItemKind::Integer:
                        Left.Value.IntVal = static_cast<XInteger>(Left.Value.BoolVal) / Right.Value.IntVal;
                        Left.Kind = EnvironmentStackItem::ItemKind::Integer;
                        break;
                    case EnvironmentStackItem::ItemKind::Decimal:
                        Left.Value.DeciVal =
                                static_cast<XDecimal>(Left.Value.BoolVal) / Right.Value.DeciVal;
                        Left.Kind = EnvironmentStackItem::ItemKind::Decimal;
                        break;
                    case EnvironmentStackItem::ItemKind::Boolean:
                        Left.Value.BoolVal *= Right.Value.BoolVal;
                        break;
                    case EnvironmentStackItem::ItemKind::FunctionPointer:
                    case EnvironmentStackItem::ItemKind::HeapPointer:
                        throw BytecodeInterpretError(L"Cannot add integers with a object.");
                    case EnvironmentStackItem::ItemKind::Null:
                        throw BytecodeInterpretError(L"Cannot add integers with a null value.");
                }
                InterpreterEnvironment.Stack.PushValueToStack(Left);
                break;
            case EnvironmentStackItem::ItemKind::FunctionPointer:
                break;
            case EnvironmentStackItem::ItemKind::HeapPointer:
                switch (InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal].Kind) {
                    case EnvObject::ObjectKind::ClassObject: {
                        auto &ClassObject = *InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal].Value.ClassObjectPointer;
                        auto &Method = InterpreterEnvironment.Heap.HeapData[ClassObject.GetMember(
                                Hash(L"__instruction_div__"))];
                        if (Method.Kind == EnvObject::ObjectKind::FunctionPointer) {
                            InterpreterEnvironment.Stack.PushValueToStack(Left); // this
                            InterpreterEnvironment.Stack.PushValueToStack(Right); // rhs
                            InterpreterEnvironment.Stack.PushValueToStack(
                                    {EnvironmentStackItem::ItemKind::FunctionPointer,
                                     (EnvironmentStackItem::ItemValue) {Method.Value.FunctionPointerValue}});
                            InstructionFuncInvoke((BytecodeStructure::InstructionParam) {static_cast<XIndexType>(2)});
                        } else {
                            throw BytecodeInterpretError(L"Member `__instruction_div__` isn't a method");
                        }
                        break;
                    }
                    case EnvObject::ObjectKind::ArrayObject:
                        throw BytecodeInterpretError(L"Unsupported array operation.");
                        break;
                    case EnvObject::ObjectKind::StringObject:
                        throw BytecodeInterpretError(L"Unsupported string operation.");
                    default:
                        throw BytecodeInterpretError(L"Cannot operate an basic-type heap item.");
                }
                break;
            case EnvironmentStackItem::ItemKind::Null:
                throw BytecodeInterpretError(L"Cannot add elements with a null value.");
        }
    }

    void BytecodeInterpreter::InstructionCalculationMod(BytecodeStructure::InstructionParam Param) {
        auto Right = InterpreterEnvironment.Stack.PopValueFromStack();
        auto Left = InterpreterEnvironment.Stack.PopValueFromStack();
        if (Left.Kind != EnvironmentStackItem::ItemKind::Integer or
            Right.Kind != EnvironmentStackItem::ItemKind::Integer) {
            throw BytecodeInterpretError(L"Command calculation_mod only can be used between 2 integers.");
        }
        Left.Value.IntVal %= Right.Value.IntVal;
        InterpreterEnvironment.Stack.PushValueToStack(Left);
    }

    void BytecodeInterpreter::InstructionLogicAnd(BytecodeStructure::InstructionParam Param) {
/* Get operands and covert type to boolean */
        auto Right = InterpreterEnvironment.Stack.PopValueFromStack();
        switch (Right.Kind) {
            case EnvironmentStackItem::ItemKind::Integer:
                Right.Value.BoolVal = Right.Value.IntVal;
                Right.Kind = EnvironmentStackItem::ItemKind::Boolean;
                break;
            case EnvironmentStackItem::ItemKind::Decimal:
                Right.Value.BoolVal = static_cast<XBoolean>(Right.Value.DeciVal);
                Right.Kind = EnvironmentStackItem::ItemKind::Boolean;
                break;
            case EnvironmentStackItem::ItemKind::FunctionPointer:
                Right.Value.BoolVal = static_cast<XBoolean>(Right.Value.FuncPointerVal);
                Right.Kind = EnvironmentStackItem::ItemKind::Boolean;
                break;
            case EnvironmentStackItem::ItemKind::HeapPointer:
                break;
            case EnvironmentStackItem::ItemKind::Null:
                Right.Value.BoolVal = false;
                Right.Kind = EnvironmentStackItem::ItemKind::Boolean;
                break;
            case EnvironmentStackItem::ItemKind::Boolean:
                break;
        }
        auto Left = InterpreterEnvironment.Stack.PopValueFromStack();
        switch (Left.Kind) {
            case EnvironmentStackItem::ItemKind::Integer:
                Left.Value.BoolVal = Left.Value.IntVal;
                Left.Kind = EnvironmentStackItem::ItemKind::Boolean;
                break;
            case EnvironmentStackItem::ItemKind::Decimal:
                Left.Value.BoolVal = static_cast<XBoolean>(Left.Value.DeciVal);
                Left.Kind = EnvironmentStackItem::ItemKind::Boolean;
                break;
            case EnvironmentStackItem::ItemKind::FunctionPointer:
                Left.Value.BoolVal = static_cast<XBoolean>(Left.Value.FuncPointerVal);
                Left.Kind = EnvironmentStackItem::ItemKind::Boolean;
                break;
            case EnvironmentStackItem::ItemKind::HeapPointer:
                switch (InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal].Kind) {
                    case EnvObject::ObjectKind::ClassObject: {
                        auto &ClassObject = *InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal].Value.ClassObjectPointer;
                        auto &Method = InterpreterEnvironment.Heap.HeapData[ClassObject.GetMember(
                                Hash(L"__instruction_logic_and__"))];
                        if (Method.Kind == EnvObject::ObjectKind::FunctionPointer) {
                            InterpreterEnvironment.Stack.PushValueToStack(Left); // this
                            InterpreterEnvironment.Stack.PushValueToStack(Right); // rhs
                            InterpreterEnvironment.Stack.PushValueToStack(
                                    {EnvironmentStackItem::ItemKind::FunctionPointer,
                                     (EnvironmentStackItem::ItemValue) {Method.Value.FunctionPointerValue}});
                            InstructionFuncInvoke((BytecodeStructure::InstructionParam) {static_cast<XIndexType>(2)});
                        } else {
                            throw BytecodeInterpretError(L"Member `__instruction_logic_and__` isn't a method");
                        }
                        return;
                    }
                    case EnvObject::ObjectKind::ArrayObject:
                        throw BytecodeInterpretError(L"Unsupported array operation.");
                    case EnvObject::ObjectKind::StringObject:
                        throw BytecodeInterpretError(L"Unsupported string operation.");
                    default:
                        throw BytecodeInterpretError(L"Cannot operate an basic-type heap item.");
                }
                break;
            case EnvironmentStackItem::ItemKind::Null:
                Left.Value.BoolVal = false;
                Left.Kind = EnvironmentStackItem::ItemKind::Boolean;
                break;
            case EnvironmentStackItem::ItemKind::Boolean:
                /* don't need to covert boolean value */
                break;
        }

        if (Right.Kind == EnvironmentStackItem::ItemKind::Boolean and
            Left.Kind == EnvironmentStackItem::ItemKind::Boolean) {
            Left.Value.BoolVal = Left.Value.BoolVal and Right.Value.BoolVal;
            InterpreterEnvironment.Stack.PushValueToStack(Left);
        } else {
            throw BytecodeInterpretError(
                    L"calculation_mod: Cannot auto-covert types of operands to boolean.");
        }
    }

    void BytecodeInterpreter::InstructionLogicOr(BytecodeStructure::InstructionParam Param) {
/* Get operands and covert type to boolean */
        auto Right = InterpreterEnvironment.Stack.PopValueFromStack();
        switch (Right.Kind) {
            case EnvironmentStackItem::ItemKind::Integer:
                Right.Value.BoolVal = Right.Value.IntVal;
                Right.Kind = EnvironmentStackItem::ItemKind::Boolean;
                break;
            case EnvironmentStackItem::ItemKind::Decimal:
                Right.Value.BoolVal = static_cast<XBoolean>(Right.Value.DeciVal);
                Right.Kind = EnvironmentStackItem::ItemKind::Boolean;
                break;
            case EnvironmentStackItem::ItemKind::FunctionPointer:
                Right.Value.BoolVal = static_cast<XBoolean>(Right.Value.FuncPointerVal);
                Right.Kind = EnvironmentStackItem::ItemKind::Boolean;
                break;
            case EnvironmentStackItem::ItemKind::HeapPointer:
                break;
            case EnvironmentStackItem::ItemKind::Null:
                Right.Value.BoolVal = false;
                Right.Kind = EnvironmentStackItem::ItemKind::Boolean;
                break;
            case EnvironmentStackItem::ItemKind::Boolean:
                /* don't need to covert boolean value to boolean value */
                break;
        }
        auto Left = InterpreterEnvironment.Stack.PopValueFromStack();
        switch (Left.Kind) {
            case EnvironmentStackItem::ItemKind::Integer:
                Left.Value.BoolVal = Left.Value.IntVal;
                Left.Kind = EnvironmentStackItem::ItemKind::Boolean;
                break;
            case EnvironmentStackItem::ItemKind::Decimal:
                Left.Value.BoolVal = static_cast<XBoolean>(Left.Value.DeciVal);
                Left.Kind = EnvironmentStackItem::ItemKind::Boolean;
                break;
            case EnvironmentStackItem::ItemKind::FunctionPointer:
                Left.Value.BoolVal = static_cast<XBoolean>(Left.Value.FuncPointerVal);
                Left.Kind = EnvironmentStackItem::ItemKind::Boolean;
                break;
            case EnvironmentStackItem::ItemKind::HeapPointer:
                switch (InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal].Kind) {
                    case EnvObject::ObjectKind::ClassObject: {
                        auto &ClassObject = *InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal].Value.ClassObjectPointer;
                        auto &Method = InterpreterEnvironment.Heap.HeapData[ClassObject.GetMember(
                                Hash(L"__instruction_logic_or__"))];
                        if (Method.Kind == EnvObject::ObjectKind::FunctionPointer) {
                            InterpreterEnvironment.Stack.PushValueToStack(Left); // this
                            InterpreterEnvironment.Stack.PushValueToStack(Right); // rhs
                            InterpreterEnvironment.Stack.PushValueToStack(
                                    {EnvironmentStackItem::ItemKind::FunctionPointer,
                                     (EnvironmentStackItem::ItemValue) {Method.Value.FunctionPointerValue}});
                            InstructionFuncInvoke((BytecodeStructure::InstructionParam) {static_cast<XIndexType>(2)});
                        } else {
                            throw BytecodeInterpretError(L"Member `__instruction_logic_or__` isn't a method");
                        }
                        return;
                    }
                    case EnvObject::ObjectKind::ArrayObject:
                        throw BytecodeInterpretError(L"Unsupported array operation.");
                    case EnvObject::ObjectKind::StringObject:
                        throw BytecodeInterpretError(L"Unsupported string operation.");
                    default:
                        throw BytecodeInterpretError(L"Cannot operate an basic-type heap item.");
                }
                break;
            case EnvironmentStackItem::ItemKind::Null:
                Left.Value.BoolVal = false;
                Left.Kind = EnvironmentStackItem::ItemKind::Boolean;
                break;
            case EnvironmentStackItem::ItemKind::Boolean:
                /* don't need to covert boolean value */
                break;
        }

        if (Right.Kind == EnvironmentStackItem::ItemKind::Boolean and
            Left.Kind == EnvironmentStackItem::ItemKind::Boolean) {
            Left.Value.BoolVal = Left.Value.BoolVal or Right.Value.BoolVal;
            InterpreterEnvironment.Stack.PushValueToStack(Left);
        } else {
            throw BytecodeInterpretError(
                    L"calculation_or: Cannot auto-covert types of operands to boolean.");
        }
    }

    void BytecodeInterpreter::InstructionLogicEqual(BytecodeStructure::InstructionParam Param) {
        auto Right = InterpreterEnvironment.Stack.PopValueFromStack();
        auto Left = InterpreterEnvironment.Stack.PopValueFromStack();
        bool Result = false;

        if (Left.Kind == Right.Kind) {
            switch (Left.Kind) {
                case EnvironmentStackItem::ItemKind::Integer:
                case EnvironmentStackItem::ItemKind::Decimal:
                case EnvironmentStackItem::ItemKind::Boolean:
                case EnvironmentStackItem::ItemKind::Null:
                case EnvironmentStackItem::ItemKind::FunctionPointer:
                    Result = Left.Value.FuncPointerVal == Right.Value.FuncPointerVal;
                    break;
                case EnvironmentStackItem::ItemKind::HeapPointer:
                    Result = InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal] ==
                             InterpreterEnvironment.Heap.HeapData[Right.Value.HeapPointerVal];
                    break;
            }
        }
        InterpreterEnvironment.Stack.PushValueToStack(
                {EnvironmentStackItem::ItemKind::Boolean, (EnvironmentStackItem::ItemValue) {Result}});
    }

    void BytecodeInterpreter::InstructionLogicNotEqual(BytecodeStructure::InstructionParam Param) {
        auto Right = InterpreterEnvironment.Stack.PopValueFromStack();
        auto Left = InterpreterEnvironment.Stack.PopValueFromStack();
        bool Result = false;

        if (Left.Kind == Right.Kind) {
            switch (Left.Kind) {
                case EnvironmentStackItem::ItemKind::Integer:
                case EnvironmentStackItem::ItemKind::Decimal:
                case EnvironmentStackItem::ItemKind::Boolean:
                case EnvironmentStackItem::ItemKind::Null:
                case EnvironmentStackItem::ItemKind::FunctionPointer:
                    Result = Left.Value.FuncPointerVal != Right.Value.FuncPointerVal;
                    break;
                case EnvironmentStackItem::ItemKind::HeapPointer:
                    Result = InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal] !=
                             InterpreterEnvironment.Heap.HeapData[Right.Value.HeapPointerVal];
                    break;
            }
        }
        InterpreterEnvironment.Stack.PushValueToStack(
                {EnvironmentStackItem::ItemKind::Boolean, (EnvironmentStackItem::ItemValue) {Result}});
    }

    void BytecodeInterpreter::InstructionLogicGreatEqual(BytecodeStructure::InstructionParam Param) {
        auto Right = InterpreterEnvironment.Stack.PopValueFromStack();
        auto Left = InterpreterEnvironment.Stack.PopValueFromStack();
        bool Result = false;

        switch (Left.Kind) {
            case EnvironmentStackItem::ItemKind::Integer:
                switch (Right.Kind) {
                    case EnvironmentStackItem::ItemKind::Integer:
                        Result = Left.Value.IntVal >= Right.Value.IntVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Decimal:
                        Result = static_cast<XDecimal>(Left.Value.IntVal) >= Right.Value.DeciVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Boolean:
                        Result = Left.Value.IntVal >= static_cast<XInteger>(Right.Value.BoolVal);
                        break;
                    case EnvironmentStackItem::ItemKind::FunctionPointer:
                    case EnvironmentStackItem::ItemKind::HeapPointer:
                        throw BytecodeInterpretError(L"Cannot compare integers with a object.");
                    case EnvironmentStackItem::ItemKind::Null:
                        throw BytecodeInterpretError(L"Cannot compare integers with a null value.");
                }
                InterpreterEnvironment.Stack.PushValueToStack({EnvironmentStackItem::ItemKind::Boolean,
                                                               (EnvironmentStackItem::ItemValue) {Result}});
                break;
            case EnvironmentStackItem::ItemKind::Decimal:
                switch (Right.Kind) {
                    case EnvironmentStackItem::ItemKind::Integer:
                        Result = Left.Value.DeciVal >= static_cast<XDecimal>(Right.Value.IntVal);
                        break;
                    case EnvironmentStackItem::ItemKind::Decimal:
                        Result = Left.Value.DeciVal >= Right.Value.DeciVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Boolean:
                        Result = Left.Value.DeciVal >= static_cast<XDecimal>(Right.Value.BoolVal);
                        break;
                    case EnvironmentStackItem::ItemKind::FunctionPointer:
                    case EnvironmentStackItem::ItemKind::HeapPointer:
                        throw BytecodeInterpretError(L"Cannot add integers with a object.");
                    case EnvironmentStackItem::ItemKind::Null:
                        throw BytecodeInterpretError(L"Cannot add integers with a null value.");
                }
                InterpreterEnvironment.Stack.PushValueToStack({EnvironmentStackItem::ItemKind::Boolean,
                                                               (EnvironmentStackItem::ItemValue) {Result}});
                break;
            case EnvironmentStackItem::ItemKind::Boolean:
                switch (Right.Kind) {
                    case EnvironmentStackItem::ItemKind::Integer:
                        Result = static_cast<XInteger>(Left.Value.BoolVal) >= Right.Value.IntVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Decimal:
                        Result = static_cast<XDecimal>(Left.Value.BoolVal) >= Right.Value.DeciVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Boolean:
                        Result = Left.Value.BoolVal >= Right.Value.BoolVal;
                        break;
                    case EnvironmentStackItem::ItemKind::FunctionPointer:
                    case EnvironmentStackItem::ItemKind::HeapPointer:
                        throw BytecodeInterpretError(L"Cannot compare integers with a object.");
                    case EnvironmentStackItem::ItemKind::Null:
                        throw BytecodeInterpretError(L"Cannot compare with a null value.");
                }
                InterpreterEnvironment.Stack.PushValueToStack({EnvironmentStackItem::ItemKind::Boolean,
                                                               (EnvironmentStackItem::ItemValue) {Result}});
                break;
            case EnvironmentStackItem::ItemKind::FunctionPointer:
            case EnvironmentStackItem::ItemKind::HeapPointer:
                switch (InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal].Kind) {
                    case EnvObject::ObjectKind::ClassObject: {
                        auto &ClassObject = *InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal].Value.ClassObjectPointer;
                        auto &Method = InterpreterEnvironment.Heap.HeapData[ClassObject.GetMember(
                                Hash(L"__instruction_logic_great_equal__"))];
                        if (Method.Kind == EnvObject::ObjectKind::FunctionPointer) {
                            InterpreterEnvironment.Stack.PushValueToStack(Left); // this
                            InterpreterEnvironment.Stack.PushValueToStack(Right); // rhs
                            InterpreterEnvironment.Stack.PushValueToStack(
                                    {EnvironmentStackItem::ItemKind::FunctionPointer,
                                     (EnvironmentStackItem::ItemValue) {Method.Value.FunctionPointerValue}});
                            InstructionFuncInvoke((BytecodeStructure::InstructionParam) {static_cast<XIndexType>(2)});
                        } else {
                            throw BytecodeInterpretError(L"Member `__instruction_logic_great_equal__` isn't a method");
                        }
                        return;
                    }
                    case EnvObject::ObjectKind::ArrayObject:
                        throw BytecodeInterpretError(L"Unsupported array operation.");
                    case EnvObject::ObjectKind::StringObject:
                        throw BytecodeInterpretError(L"Unsupported string operation.");
                    default:
                        throw BytecodeInterpretError(L"Cannot operate an basic-type heap item.");
                }
                break;
            case EnvironmentStackItem::ItemKind::Null:
                throw BytecodeInterpretError(L"Cannot add elements with a null value.");
        }
    }

    void BytecodeInterpreter::InstructionLogicLessEqual(BytecodeStructure::InstructionParam Param) {
        auto Right = InterpreterEnvironment.Stack.PopValueFromStack();
        auto Left = InterpreterEnvironment.Stack.PopValueFromStack();
        bool Result = false;

        switch (Left.Kind) {
            case EnvironmentStackItem::ItemKind::Integer:
                switch (Right.Kind) {
                    case EnvironmentStackItem::ItemKind::Integer:
                        Result = Left.Value.IntVal <= Right.Value.IntVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Decimal:
                        Result = static_cast<XDecimal>(Left.Value.IntVal) <= Right.Value.DeciVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Boolean:
                        Result = Left.Value.IntVal <= static_cast<XInteger>(Right.Value.BoolVal);
                        break;
                    case EnvironmentStackItem::ItemKind::FunctionPointer:
                    case EnvironmentStackItem::ItemKind::HeapPointer:
                        throw BytecodeInterpretError(L"Cannot compare integers with a object.");
                    case EnvironmentStackItem::ItemKind::Null:
                        throw BytecodeInterpretError(L"Cannot compare integers with a null value.");
                }
                InterpreterEnvironment.Stack.PushValueToStack({EnvironmentStackItem::ItemKind::Boolean,
                                                               (EnvironmentStackItem::ItemValue) {Result}});
                break;
            case EnvironmentStackItem::ItemKind::Decimal:
                switch (Right.Kind) {
                    case EnvironmentStackItem::ItemKind::Integer:
                        Result = Left.Value.DeciVal <= static_cast<XDecimal>(Right.Value.IntVal);
                        break;
                    case EnvironmentStackItem::ItemKind::Decimal:
                        Result = Left.Value.DeciVal <= Right.Value.DeciVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Boolean:
                        Result = Left.Value.DeciVal <= static_cast<XDecimal>(Right.Value.BoolVal);
                        break;
                    case EnvironmentStackItem::ItemKind::FunctionPointer:
                    case EnvironmentStackItem::ItemKind::HeapPointer:
                        throw BytecodeInterpretError(L"Cannot add integers with a object.");
                    case EnvironmentStackItem::ItemKind::Null:
                        throw BytecodeInterpretError(L"Cannot add integers with a null value.");
                }
                InterpreterEnvironment.Stack.PushValueToStack({EnvironmentStackItem::ItemKind::Boolean,
                                                               (EnvironmentStackItem::ItemValue) {Result}});
                break;
            case EnvironmentStackItem::ItemKind::Boolean:
                switch (Right.Kind) {
                    case EnvironmentStackItem::ItemKind::Integer:
                        Result = static_cast<XInteger>(Left.Value.BoolVal) <= Right.Value.IntVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Decimal:
                        Result = static_cast<XDecimal>(Left.Value.BoolVal) <= Right.Value.DeciVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Boolean:
                        Result = Left.Value.BoolVal <= Right.Value.BoolVal;
                        break;
                    case EnvironmentStackItem::ItemKind::FunctionPointer:
                    case EnvironmentStackItem::ItemKind::HeapPointer:
                        throw BytecodeInterpretError(L"Cannot compare integers with a object.");
                    case EnvironmentStackItem::ItemKind::Null:
                        throw BytecodeInterpretError(L"Cannot compare with a null value.");
                }
                InterpreterEnvironment.Stack.PushValueToStack({EnvironmentStackItem::ItemKind::Boolean,
                                                               (EnvironmentStackItem::ItemValue) {Result}});
                break;
            case EnvironmentStackItem::ItemKind::HeapPointer:
                switch (InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal].Kind) {
                    case EnvObject::ObjectKind::ClassObject: {
                        auto &ClassObject = *InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal].Value.ClassObjectPointer;
                        auto &Method = InterpreterEnvironment.Heap.HeapData[ClassObject.GetMember(
                                Hash(L"__instruction_logic_less_equal__"))];
                        if (Method.Kind == EnvObject::ObjectKind::FunctionPointer) {
                            InterpreterEnvironment.Stack.PushValueToStack(Left); // this
                            InterpreterEnvironment.Stack.PushValueToStack(Right); // rhs
                            InterpreterEnvironment.Stack.PushValueToStack(
                                    {EnvironmentStackItem::ItemKind::FunctionPointer,
                                     (EnvironmentStackItem::ItemValue) {Method.Value.FunctionPointerValue}});
                            InstructionFuncInvoke((BytecodeStructure::InstructionParam) {static_cast<XIndexType>(2)});
                        } else {
                            throw BytecodeInterpretError(L"Member `__instruction_logic_less_equal__` isn't a method");
                        }
                        return;
                    }
                    case EnvObject::ObjectKind::ArrayObject:
                        throw BytecodeInterpretError(L"Unsupported array operation.");
                    case EnvObject::ObjectKind::StringObject:
                        throw BytecodeInterpretError(L"Unsupported string operation.");
                    default:
                        throw BytecodeInterpretError(L"Cannot operate an basic-type heap item.");
                }
                break;
            case EnvironmentStackItem::ItemKind::Null:
                throw BytecodeInterpretError(L"Cannot add elements with a null value.");
            case EnvironmentStackItem::ItemKind::FunctionPointer:
                break;
        }
    }

    void BytecodeInterpreter::InstructionLogicGreat(BytecodeStructure::InstructionParam Param) {
        auto Right = InterpreterEnvironment.Stack.PopValueFromStack();
        auto Left = InterpreterEnvironment.Stack.PopValueFromStack();
        bool Result = false;

        switch (Left.Kind) {
            case EnvironmentStackItem::ItemKind::Integer:
                switch (Right.Kind) {
                    case EnvironmentStackItem::ItemKind::Integer:
                        Result = Left.Value.IntVal > Right.Value.IntVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Decimal:
                        Result = static_cast<XDecimal>(Left.Value.IntVal) > Right.Value.DeciVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Boolean:
                        Result = Left.Value.IntVal > static_cast<XInteger>(Right.Value.BoolVal);
                        break;
                    case EnvironmentStackItem::ItemKind::FunctionPointer:
                    case EnvironmentStackItem::ItemKind::HeapPointer:
                        throw BytecodeInterpretError(L"Cannot compare integers with a object.");
                    case EnvironmentStackItem::ItemKind::Null:
                        throw BytecodeInterpretError(L"Cannot compare integers with a null value.");
                }
                InterpreterEnvironment.Stack.PushValueToStack({EnvironmentStackItem::ItemKind::Boolean,
                                                               (EnvironmentStackItem::ItemValue) {Result}});
                break;
            case EnvironmentStackItem::ItemKind::Decimal:
                switch (Right.Kind) {
                    case EnvironmentStackItem::ItemKind::Integer:
                        Result = Left.Value.DeciVal > static_cast<XDecimal>(Right.Value.IntVal);
                        break;
                    case EnvironmentStackItem::ItemKind::Decimal:
                        Result = Left.Value.DeciVal > Right.Value.DeciVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Boolean:
                        Result = Left.Value.DeciVal > static_cast<XDecimal>(Right.Value.BoolVal);
                        break;
                    case EnvironmentStackItem::ItemKind::FunctionPointer:
                    case EnvironmentStackItem::ItemKind::HeapPointer:
                        throw BytecodeInterpretError(L"Cannot add integers with a object.");
                    case EnvironmentStackItem::ItemKind::Null:
                        throw BytecodeInterpretError(L"Cannot add integers with a null value.");
                }
                InterpreterEnvironment.Stack.PushValueToStack({EnvironmentStackItem::ItemKind::Boolean,
                                                               (EnvironmentStackItem::ItemValue) {Result}});
                break;
            case EnvironmentStackItem::ItemKind::Boolean:
                switch (Right.Kind) {
                    case EnvironmentStackItem::ItemKind::Integer:
                        Result = static_cast<XInteger>(Left.Value.BoolVal) > Right.Value.IntVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Decimal:
                        Result = static_cast<XDecimal>(Left.Value.BoolVal) > Right.Value.DeciVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Boolean:
                        Result = Left.Value.BoolVal > Right.Value.BoolVal;
                        break;
                    case EnvironmentStackItem::ItemKind::FunctionPointer:
                    case EnvironmentStackItem::ItemKind::HeapPointer:
                        throw BytecodeInterpretError(L"Cannot compare integers with a object.");
                    case EnvironmentStackItem::ItemKind::Null:
                        throw BytecodeInterpretError(L"Cannot compare with a null value.");
                }
                InterpreterEnvironment.Stack.PushValueToStack({EnvironmentStackItem::ItemKind::Boolean,
                                                               (EnvironmentStackItem::ItemValue) {Result}});
                break;
            case EnvironmentStackItem::ItemKind::HeapPointer:
                switch (InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal].Kind) {
                    case EnvObject::ObjectKind::ClassObject: {
                        auto &ClassObject = *InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal].Value.ClassObjectPointer;
                        auto &Method = InterpreterEnvironment.Heap.HeapData[ClassObject.GetMember(
                                Hash(L"__instruction_logic_great__"))];
                        if (Method.Kind == EnvObject::ObjectKind::FunctionPointer) {
                            InterpreterEnvironment.Stack.PushValueToStack(Left); // this
                            InterpreterEnvironment.Stack.PushValueToStack(Right); // rhs
                            InterpreterEnvironment.Stack.PushValueToStack(
                                    {EnvironmentStackItem::ItemKind::FunctionPointer,
                                     (EnvironmentStackItem::ItemValue) {Method.Value.FunctionPointerValue}});
                            InstructionFuncInvoke((BytecodeStructure::InstructionParam) {static_cast<XIndexType>(2)});
                        } else {
                            throw BytecodeInterpretError(L"Member `__instruction_logic_great__` isn't a method");
                        }
                        return;
                    }
                    case EnvObject::ObjectKind::ArrayObject:
                        throw BytecodeInterpretError(L"Unsupported array operation.");
                    case EnvObject::ObjectKind::StringObject:
                        throw BytecodeInterpretError(L"Unsupported string operation.");
                    default:
                        throw BytecodeInterpretError(L"Cannot operate an basic-type heap item.");
                }
                break;
            case EnvironmentStackItem::ItemKind::Null:
                throw BytecodeInterpretError(L"Cannot add elements with a null value.");
            case EnvironmentStackItem::ItemKind::FunctionPointer:
                throw BytecodeInterpretError(L"Cannot add elements with a function pointer value.");
        }
    }

    void BytecodeInterpreter::InstructionLogicLess(BytecodeStructure::InstructionParam Param) {
        auto Right = InterpreterEnvironment.Stack.PopValueFromStack();
        auto Left = InterpreterEnvironment.Stack.PopValueFromStack();
        bool Result = false;

        switch (Left.Kind) {
            case EnvironmentStackItem::ItemKind::Integer:
                switch (Right.Kind) {
                    case EnvironmentStackItem::ItemKind::Integer:
                        Result = Left.Value.IntVal < Right.Value.IntVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Decimal:
                        Result = static_cast<XDecimal>(Left.Value.IntVal) < Right.Value.DeciVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Boolean:
                        Result = Left.Value.IntVal < static_cast<XInteger>(Right.Value.BoolVal);
                        break;
                    case EnvironmentStackItem::ItemKind::FunctionPointer:
                    case EnvironmentStackItem::ItemKind::HeapPointer:
                        throw BytecodeInterpretError(L"Cannot compare integers with a object.");
                    case EnvironmentStackItem::ItemKind::Null:
                        throw BytecodeInterpretError(L"Cannot compare integers with a null value.");
                }
                InterpreterEnvironment.Stack.PushValueToStack({EnvironmentStackItem::ItemKind::Boolean,
                                                               (EnvironmentStackItem::ItemValue) {Result}});
                break;
            case EnvironmentStackItem::ItemKind::Decimal:
                switch (Right.Kind) {
                    case EnvironmentStackItem::ItemKind::Integer:
                        Result = Left.Value.DeciVal < static_cast<XDecimal>(Right.Value.IntVal);
                        break;
                    case EnvironmentStackItem::ItemKind::Decimal:
                        Result = Left.Value.DeciVal < Right.Value.DeciVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Boolean:
                        Result = Left.Value.DeciVal < static_cast<XDecimal>(Right.Value.BoolVal);
                        break;
                    case EnvironmentStackItem::ItemKind::FunctionPointer:
                    case EnvironmentStackItem::ItemKind::HeapPointer:
                        throw BytecodeInterpretError(L"Cannot add integers with a object.");
                    case EnvironmentStackItem::ItemKind::Null:
                        throw BytecodeInterpretError(L"Cannot add integers with a null value.");
                }
                InterpreterEnvironment.Stack.PushValueToStack({EnvironmentStackItem::ItemKind::Boolean,
                                                               (EnvironmentStackItem::ItemValue) {Result}});
                break;
            case EnvironmentStackItem::ItemKind::Boolean:
                switch (Right.Kind) {
                    case EnvironmentStackItem::ItemKind::Integer:
                        Result = static_cast<XInteger>(Left.Value.BoolVal) < Right.Value.IntVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Decimal:
                        Result = static_cast<XDecimal>(Left.Value.BoolVal) < Right.Value.DeciVal;
                        break;
                    case EnvironmentStackItem::ItemKind::Boolean:
                        Result = Left.Value.BoolVal < Right.Value.BoolVal;
                        break;
                    case EnvironmentStackItem::ItemKind::FunctionPointer:
                    case EnvironmentStackItem::ItemKind::HeapPointer:
                        throw BytecodeInterpretError(L"Cannot compare integers with a object.");
                    case EnvironmentStackItem::ItemKind::Null:
                        throw BytecodeInterpretError(L"Cannot compare with a null value.");
                }
                InterpreterEnvironment.Stack.PushValueToStack({EnvironmentStackItem::ItemKind::Boolean,
                                                               (EnvironmentStackItem::ItemValue) {Result}});
                break;
            case EnvironmentStackItem::ItemKind::HeapPointer:
                switch (InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal].Kind) {
                    case EnvObject::ObjectKind::ClassObject: {
                        auto &ClassObject = *InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal].Value.ClassObjectPointer;
                        auto &Method = InterpreterEnvironment.Heap.HeapData[ClassObject.GetMember(
                                Hash(L"__instruction_logic_less__"))];
                        if (Method.Kind == EnvObject::ObjectKind::FunctionPointer) {
                            InterpreterEnvironment.Stack.PushValueToStack(Left); // this
                            InterpreterEnvironment.Stack.PushValueToStack(Right); // rhs
                            InterpreterEnvironment.Stack.PushValueToStack(
                                    {EnvironmentStackItem::ItemKind::FunctionPointer,
                                     (EnvironmentStackItem::ItemValue) {Method.Value.FunctionPointerValue}});
                            InstructionFuncInvoke((BytecodeStructure::InstructionParam) {static_cast<XIndexType>(2)});
                        } else {
                            throw BytecodeInterpretError(L"Member `__instruction_logic_less__` isn't a method");
                        }
                        return;
                    }
                    case EnvObject::ObjectKind::ArrayObject:
                        throw BytecodeInterpretError(L"Unsupported array operation.");
                    case EnvObject::ObjectKind::StringObject:
                        throw BytecodeInterpretError(L"Unsupported string operation.");
                    default:
                        throw BytecodeInterpretError(L"Cannot operate an basic-type heap item.");
                }
                break;
            case EnvironmentStackItem::ItemKind::Null:
                throw BytecodeInterpretError(L"Cannot add elements with a null value.");
        }
    }

    void BytecodeInterpreter::InstructionBinaryAnd(BytecodeStructure::InstructionParam Param) {
        /* get two operands from the stack */
        auto Right = InterpreterEnvironment.Stack.PopValueFromStack();
        auto Left = InterpreterEnvironment.Stack.PopValueFromStack();

        if (Right.Kind != EnvironmentStackItem::ItemKind::HeapPointer and
            Right.Kind != EnvironmentStackItem::ItemKind::Null and
            Left.Kind != EnvironmentStackItem::ItemKind::HeapPointer and
            Left.Kind != EnvironmentStackItem::ItemKind::Null) {
            Left.Value.IntVal = Left.Value.IntVal & Right.Value.IntVal;
        } else {
            throw BytecodeInterpretError(L"binary_and: unexpected operands");
        }
        InterpreterEnvironment.Stack.PushValueToStack(Left);
    }

    void BytecodeInterpreter::InstructionBinaryOr(BytecodeStructure::InstructionParam Param) {
        /* get two operands from the stack */
        auto Right = InterpreterEnvironment.Stack.PopValueFromStack();
        auto Left = InterpreterEnvironment.Stack.PopValueFromStack();

        if (Right.Kind != EnvironmentStackItem::ItemKind::HeapPointer and
            Right.Kind != EnvironmentStackItem::ItemKind::Null and
            Left.Kind != EnvironmentStackItem::ItemKind::HeapPointer and
            Left.Kind != EnvironmentStackItem::ItemKind::Null) {
            Left.Value.IntVal = Left.Value.IntVal | Right.Value.IntVal;
        } else {
            throw BytecodeInterpretError(L"binary_or: unexpected operands");
        }
        InterpreterEnvironment.Stack.PushValueToStack(Left);
    }

    void BytecodeInterpreter::InstructionBinaryXOR(BytecodeStructure::InstructionParam Param) {
        /* get two operands from the stack */
        auto Right = InterpreterEnvironment.Stack.PopValueFromStack();
        auto Left = InterpreterEnvironment.Stack.PopValueFromStack();

        if (Right.Kind != EnvironmentStackItem::ItemKind::HeapPointer and
            Right.Kind != EnvironmentStackItem::ItemKind::Null and
            Left.Kind != EnvironmentStackItem::ItemKind::HeapPointer and
            Left.Kind != EnvironmentStackItem::ItemKind::Null) {
            Left.Value.IntVal = Left.Value.IntVal ^ Right.Value.IntVal;
        } else {
            throw BytecodeInterpretError(L"binary_and: unexpected operands");
        }
        InterpreterEnvironment.Stack.PushValueToStack(Left);
    }

    void BytecodeInterpreter::InstructionBinaryNot(BytecodeStructure::InstructionParam Param) {
        /* get operand from the stack */
        auto Left = InterpreterEnvironment.Stack.PopValueFromStack();

        if (Left.Kind != EnvironmentStackItem::ItemKind::HeapPointer and
            Left.Kind != EnvironmentStackItem::ItemKind::Null) {
            Left.Value.IntVal = !Left.Value.IntVal;
        } else {
            throw BytecodeInterpretError(L"binary_and: unexpected operands");
        }
        InterpreterEnvironment.Stack.PushValueToStack(Left);
    }

    void BytecodeInterpreter::InstructionBinaryLM(BytecodeStructure::InstructionParam Param) {
        auto Right = InterpreterEnvironment.Stack.PopValueFromStack();
        auto Left = InterpreterEnvironment.Stack.PopValueFromStack();

        Left.Value.IntVal = Left.Value.IntVal << Right.Value.HeapPointerVal;
        InterpreterEnvironment.Stack.PushValueToStack(Left);
    }

    void BytecodeInterpreter::InstructionBinaryRM(BytecodeStructure::InstructionParam Param) {
        auto Right = InterpreterEnvironment.Stack.PopValueFromStack();
        auto Left = InterpreterEnvironment.Stack.PopValueFromStack();

        Left.Value.IntVal = Left.Value.IntVal >> Right.Value.HeapPointerVal;
    }

    void BytecodeInterpreter::InstructionStackPushInteger(BytecodeStructure::InstructionParam Param) {
        InterpreterEnvironment.Stack.PushValueToStack({EnvironmentStackItem::ItemKind::Integer,
                                                       (EnvironmentStackItem::ItemValue) {Param.IntValue}
                                                      });
    }

    void BytecodeInterpreter::InstructionStackPushDecimal(BytecodeStructure::InstructionParam Param) {
        InterpreterEnvironment.Stack.PushValueToStack({EnvironmentStackItem::ItemKind::Decimal,
                                                       (EnvironmentStackItem::ItemValue) {
                                                               Param.DeciValue}});
    }

    void BytecodeInterpreter::InstructionStackPushBoolean(BytecodeStructure::InstructionParam Param) {
        InterpreterEnvironment.Stack.PushValueToStack({EnvironmentStackItem::ItemKind::Boolean,
                                                       (EnvironmentStackItem::ItemValue) {
                                                               Param.BoolValue}});
    }

    void BytecodeInterpreter::InstructionStackPushEmpty(BytecodeStructure::InstructionParam Param) {
        InterpreterEnvironment.Stack.PushValueToStack({EnvironmentStackItem::ItemKind::Null,
                                                       (EnvironmentStackItem::ItemValue) {(XIndexType) 0}});
    }

    void BytecodeInterpreter::InstructionStackPop(BytecodeStructure::InstructionParam Param) {
        InterpreterEnvironment.Stack.PopValueFromStack();
    }

    void BytecodeInterpreter::InstructionStackDuplicate(BytecodeStructure::InstructionParam Param) {
        InterpreterEnvironment.Stack.PushValueToStack(InterpreterEnvironment.Stack.GetValueFromStack(
                Param.HeapPointerValue));
    }

    void BytecodeInterpreter::InstructionStackGetTop(BytecodeStructure::InstructionParam Param) {
        InterpreterEnvironment.Stack.PushValueToStack(
                InterpreterEnvironment.Stack.Elements[InterpreterEnvironment.Stack.Elements.size() - 1 -
                                                      Param.HeapPointerValue]);
    }

    void BytecodeInterpreter::InstructionStackStore(BytecodeStructure::InstructionParam Param) {
        EnvironmentStackItem Element = InterpreterEnvironment.Stack.PopValueFromStack();
        InterpreterEnvironment.Stack.StoreValueToIndex(Param.HeapPointerValue, Element);
    }

    void BytecodeInterpreter::InstructionStaticStore(BytecodeStructure::InstructionParam Param) {
        EnvironmentStackItem Element = InterpreterEnvironment.Stack.PopValueFromStack();
        InterpreterEnvironment.Packages[InterpreterEnvironment.ProgramCounter.Package].SetStatic(Param.HeapPointerValue,
                                                                                                 Element);
    }

    void BytecodeInterpreter::InstructionConstantsLoad(BytecodeStructure::InstructionParam Param) {
        GC.Start();
        auto &Element = InterpreterEnvironment.Packages[InterpreterEnvironment.ProgramCounter.Package].Constants[Param.HeapPointerValue];
        switch (Element.Kind) {
            case EnvConstantPool::EnvConstant::ItemKind::StringVal:
                InterpreterEnvironment.Stack.PushValueToStack(
                        (EnvironmentStackItem) {EnvironmentStackItem::ItemKind::HeapPointer,
                                                (EnvironmentStackItem::ItemValue) {
                                                        InterpreterEnvironment.Heap.PushElement(
                                                                (EnvObject) {EnvObject::ObjectKind::StringObject,
                                                                             (EnvObject::ObjectValue) {
                                                                                     CreateEnvStringObjectFromXString(
                                                                                             Element.Value)}})}
                        });

                break;
        }
    }

    void BytecodeInterpreter::InstructionCalculationNegate(BytecodeStructure::InstructionParam Param) {
        EnvironmentStackItem Element = InterpreterEnvironment.Stack.PopValueFromStack();
        switch (Element.Kind) {
            case EnvironmentStackItem::ItemKind::Integer:
                Element.Value.IntVal = -Element.Value.IntVal;
                break;
            case EnvironmentStackItem::ItemKind::Decimal:
                Element.Value.DeciVal = -Element.Value.DeciVal;
                break;
            case EnvironmentStackItem::ItemKind::Boolean:
                Element.Value.BoolVal = -Element.Value.BoolVal;
                break;
            case EnvironmentStackItem::ItemKind::FunctionPointer:
            case EnvironmentStackItem::ItemKind::HeapPointer:
            case EnvironmentStackItem::ItemKind::Null:
                throw BytecodeInterpretError(L"calculation_negate: Unexpected input.");
        }
        InterpreterEnvironment.Stack.PushValueToStack(Element);
    }

    void BytecodeInterpreter::InstructionListNew(BytecodeStructure::InstructionParam Param) {
        GC.Start();
        EnvironmentStackItem ListItem{};
        ListItem.Kind = EnvironmentStackItem::ItemKind::HeapPointer;
        ListItem.Value.HeapPointerVal = InterpreterEnvironment.Heap.PushElement(
                (EnvObject) {EnvObject::ObjectKind::ArrayObject,
                             (EnvObject::ObjectValue) {NewEnvArrayObject(
                                     Param.HeapPointerValue)}});
        for (XIndexType I = 0; I < Param.HeapPointerValue; I++) {
            EnvironmentStackItem Item = InterpreterEnvironment.Stack.PopValueFromStack();
            EnvObject Object;
            switch (Item.Kind) {
                case EnvironmentStackItem::ItemKind::Integer:
                    Object.Kind = EnvObject::ObjectKind::Integer;
                    Object.Value.IntegerValue = Item.Value.IntVal;
                    break;
                case EnvironmentStackItem::ItemKind::Decimal:
                    Object.Kind = EnvObject::ObjectKind::Decimal;
                    Object.Value.IntegerValue = Item.Value.IntVal;
                    break;
                case EnvironmentStackItem::ItemKind::Boolean:
                    Object.Kind = EnvObject::ObjectKind::Boolean;
                    Object.Value.IntegerValue = Item.Value.IntVal;
                    break;
                case EnvironmentStackItem::ItemKind::FunctionPointer:
                    Object.Kind = EnvObject::ObjectKind::FunctionPointer;
                    Object.Value.FunctionPointerValue = Item.Value.FuncPointerVal;
                    break;
                case EnvironmentStackItem::ItemKind::HeapPointer:
                    Object = InterpreterEnvironment.Heap.HeapData[Item.Value.HeapPointerVal];
                    break;
                case EnvironmentStackItem::ItemKind::Null:
                    Object.Kind = EnvObject::ObjectKind::Integer;
                    break;
            }

            InterpreterEnvironment.Heap.HeapData[ListItem.Value.HeapPointerVal].Value.ArrayObjectPointer->Elements[
                    Param.HeapPointerValue - I] =
                    InterpreterEnvironment.Heap.PushElement(Object);
        }
        InterpreterEnvironment.Stack.PushValueToStack(ListItem);
    }

    void BytecodeInterpreter::InstructionListPop(BytecodeStructure::InstructionParam Param) {
        EnvironmentStackItem ListItem = InterpreterEnvironment.Stack.PopValueFromStack();
        if (ListItem.Kind == EnvironmentStackItem::ItemKind::HeapPointer and
            InterpreterEnvironment.Heap.HeapData[ListItem.Value.HeapPointerVal].Kind ==
            EnvObject::ObjectKind::ArrayObject) {
            InterpreterEnvironment.Heap.HeapData[ListItem.Value.HeapPointerVal].Value.ArrayObjectPointer->Elements.pop_back();
        }
    }

    void BytecodeInterpreter::InstructionListPush(BytecodeStructure::InstructionParam Param) {
        EnvironmentStackItem ListItem = InterpreterEnvironment.Stack.PopValueFromStack();
        if (ListItem.Kind == EnvironmentStackItem::ItemKind::HeapPointer and
            InterpreterEnvironment.Heap.HeapData[ListItem.Value.HeapPointerVal].Kind ==
            EnvObject::ObjectKind::ArrayObject) {
            EnvironmentStackItem Item = InterpreterEnvironment.Stack.PopValueFromStack();
            EnvObject Object{};
            switch (Item.Kind) {
                case EnvironmentStackItem::ItemKind::Integer:
                    Object.Kind = EnvObject::ObjectKind::Integer;
                    Object.Value.IntegerValue = Item.Value.IntVal;
                    break;
                case EnvironmentStackItem::ItemKind::Decimal:
                    Object.Kind = EnvObject::ObjectKind::Decimal;
                    Object.Value.IntegerValue = Item.Value.IntVal;
                    break;
                case EnvironmentStackItem::ItemKind::Boolean:
                    Object.Kind = EnvObject::ObjectKind::Boolean;
                    Object.Value.IntegerValue = Item.Value.IntVal;
                    break;
                case EnvironmentStackItem::ItemKind::FunctionPointer:
                    Object = (EnvObject) {
                            EnvObject::ObjectKind::FunctionPointer,
                            (EnvObject::ObjectValue) {Item.Value.FuncPointerVal}};
                    break;
                case EnvironmentStackItem::ItemKind::HeapPointer:
                    Object = InterpreterEnvironment.Heap.HeapData[Item.Value.HeapPointerVal];
                    break;
                case EnvironmentStackItem::ItemKind::Null:
                    Object.Kind = EnvObject::ObjectKind::Integer;
                    break;
            }

            InterpreterEnvironment.Heap.HeapData[ListItem.Value.HeapPointerVal].Value.ArrayObjectPointer->Elements.push_back(
                    InterpreterEnvironment.Heap.PushElement(Object));
        }
    }

    void BytecodeInterpreter::InstructionListGetMember(BytecodeStructure::InstructionParam Param) {
        EnvironmentStackItem ListItem = InterpreterEnvironment.Stack.PopValueFromStack();
        EnvironmentStackItem Index = InterpreterEnvironment.Stack.PopValueFromStack();
        if (ListItem.Kind == EnvironmentStackItem::ItemKind::HeapPointer) {
            switch (InterpreterEnvironment.Heap.HeapData[ListItem.Value.HeapPointerVal].Kind) {
                case EnvObject::ObjectKind::ArrayObject: {
                    /* 不做类型检查 */
                    EnvironmentStackItem Item{EnvironmentStackItem::ItemKind::HeapPointer,
                                              (EnvironmentStackItem::ItemValue) {
                                                      InterpreterEnvironment.Heap.HeapData[ListItem.Value.HeapPointerVal].Value.ArrayObjectPointer->Elements[Index.Value.IntVal]}};

                    InterpreterEnvironment.Stack.PushValueToStack(Item);
                    break;
                }
                case EnvObject::ObjectKind::ClassObject: {
                    auto &ClassObject = *InterpreterEnvironment.Heap.HeapData[ListItem.Value.HeapPointerVal].Value.ClassObjectPointer;
                    auto &Method = InterpreterEnvironment.Heap.HeapData[ClassObject.GetMember(
                            Hash(L"__instruction_indexOf__"))];
                    if (Method.Kind == EnvObject::ObjectKind::FunctionPointer) {
                        InterpreterEnvironment.Stack.PushValueToStack(ListItem); // this
                        InterpreterEnvironment.Stack.PushValueToStack(Index); // rhs
                        InterpreterEnvironment.Stack.PushValueToStack(
                                {EnvironmentStackItem::ItemKind::FunctionPointer,
                                 (EnvironmentStackItem::ItemValue) {Method.Value.FunctionPointerValue}});
                        ProgramCounterInformation Info = InterpreterEnvironment.ProgramCounter;
                        InstructionFuncInvoke((BytecodeStructure::InstructionParam) {static_cast<XIndexType>(2)});
                        InterpreterEnvironment.ProgramCounter = Info;
                    } else {
                        throw BytecodeInterpretError(L"Member `__instruction_indexOf__` isn't a method");
                    }
                    break;
                }
            }
        } else {
            throw BytecodeInterpretError(L"list_get_member: Unknown item type");
        }
    }

    void BytecodeInterpreter::InstructionObjectStore(BytecodeStructure::InstructionParam Param) {
        GC.Start();
        EnvironmentStackItem LeftValue = InterpreterEnvironment.Stack.PopValueFromStack();
        EnvironmentStackItem RightValue = InterpreterEnvironment.Stack.PopValueFromStack();

        switch (RightValue.Kind) {
            case EnvironmentStackItem::ItemKind::Integer:
                InterpreterEnvironment.Heap.HeapData[LeftValue.Value.HeapPointerVal] = (EnvObject) {
                        EnvObject::ObjectKind::Integer,
                        (EnvObject::ObjectValue) {RightValue.Value.IntVal}};
                break;
            case EnvironmentStackItem::ItemKind::Decimal:
                InterpreterEnvironment.Heap.HeapData[LeftValue.Value.HeapPointerVal] = (EnvObject) {
                        EnvObject::ObjectKind::Decimal,
                        (EnvObject::ObjectValue) {RightValue.Value.DeciVal}};
                break;
            case EnvironmentStackItem::ItemKind::Boolean:
                InterpreterEnvironment.Heap.HeapData[LeftValue.Value.HeapPointerVal] = (EnvObject) {
                        EnvObject::ObjectKind::Boolean,
                        (EnvObject::ObjectValue) {RightValue.Value.BoolVal}};
                break;
            case EnvironmentStackItem::ItemKind::FunctionPointer:
                InterpreterEnvironment.Heap.HeapData[LeftValue.Value.HeapPointerVal] = (EnvObject) {
                        EnvObject::ObjectKind::FunctionPointer,
                        (EnvObject::ObjectValue) {RightValue.Value.FuncPointerVal}};
                break;
            case EnvironmentStackItem::ItemKind::HeapPointer:
                InterpreterEnvironment.Heap.HeapData[LeftValue.Value.HeapPointerVal] = InterpreterEnvironment.Heap.HeapData[RightValue.Value.HeapPointerVal];
                break;
            case EnvironmentStackItem::ItemKind::Null:
                throw BytecodeInterpretError(L"object_store: cannot assign null to a heap value");
        }
    }

    void BytecodeInterpreter::InstructionObjectLvalue2Rvalue(BytecodeStructure::InstructionParam Param) {
        EnvironmentStackItem Item = InterpreterEnvironment.Stack.PopValueFromStack();

        if (Item.Kind == EnvironmentStackItem::ItemKind::HeapPointer) {
            auto Object = InterpreterEnvironment.Heap.HeapData[Item.Value.HeapPointerVal];
            switch (Object.Kind) {
                case EnvObject::ObjectKind::ClassObject:
                case EnvObject::ObjectKind::ArrayObject:
                case EnvObject::ObjectKind::StringObject:
                    break;
                case EnvObject::ObjectKind::Integer:
                    Item.Kind = EnvironmentStackItem::ItemKind::Integer;
                    Item.Value.IntVal = Object.Value.IntegerValue;
                    break;
                case EnvObject::ObjectKind::Decimal:
                    Item.Kind = EnvironmentStackItem::ItemKind::Decimal;
                    Item.Value.IntVal = Object.Value.IntegerValue;
                    break;
                case EnvObject::ObjectKind::Boolean:
                    Item.Kind = EnvironmentStackItem::ItemKind::Boolean;
                    Item.Value.IntVal = Object.Value.IntegerValue;
                    break;
                case EnvObject::ObjectKind::Index:
                    Item.Kind = EnvironmentStackItem::ItemKind::HeapPointer;
                    Item.Value.HeapPointerVal = Object.Value.IndexValue;
                    break;
                case EnvObject::ObjectKind::FunctionPointer:
                    Item.Kind = EnvironmentStackItem::ItemKind::FunctionPointer;
                    Item.Value.FuncPointerVal = Object.Value.FunctionPointerValue;
                    break;
                case EnvObject::ObjectKind::NativeMethodPointer:
                    Item.Kind = EnvironmentStackItem::ItemKind::NativeMethodPointer;
                    Item.Value.NativeMethodPointerVal = Object.Value.NativeMethodPointerValue;
                    break;
            }

            /* 如果为基础类型则转换为rvalue，否则保持原状 */
            InterpreterEnvironment.Stack.PushValueToStack(Item);
        } else {
            InterpreterEnvironment.Stack.PushValueToStack(Item);
        }
    }

    void BytecodeInterpreter::InstructionPCJumpIfTrue(BytecodeStructure::InstructionParam Param) {
        EnvironmentStackItem Element = InterpreterEnvironment.Stack.PopValueFromStack();
        bool Flag = false;
        switch (Element.Kind) {
            case EnvironmentStackItem::ItemKind::Integer:
                Flag = Element.Value.IntVal;
                break;
            case EnvironmentStackItem::ItemKind::Decimal:
                Flag = static_cast<XInteger>(Element.Value.DeciVal);
                break;
            case EnvironmentStackItem::ItemKind::Boolean:
                Flag = Element.Value.BoolVal;
                break;
            case EnvironmentStackItem::ItemKind::HeapPointer:
                Flag = Element.Value.HeapPointerVal;
                break;
            case EnvironmentStackItem::ItemKind::FunctionPointer:
                Flag = Element.Value.FuncPointerVal;
                break;
            case EnvironmentStackItem::ItemKind::Null:
                Flag = false;
                break;
        }

        if (Flag) {
            InterpreterEnvironment.ProgramCounter.NowIndex += Param.IntValue - 1;
        }
    }

    void BytecodeInterpreter::InstructionPCJumpIfFalse(BytecodeStructure::InstructionParam Param) {
        EnvironmentStackItem Element = InterpreterEnvironment.Stack.PopValueFromStack();
        bool Flag = false;
        switch (Element.Kind) {
            case EnvironmentStackItem::ItemKind::Integer:
                Flag = Element.Value.IntVal;
                break;
            case EnvironmentStackItem::ItemKind::Decimal:
                Flag = static_cast<XInteger>(Element.Value.DeciVal);
                break;
            case EnvironmentStackItem::ItemKind::Boolean:
                Flag = Element.Value.BoolVal;
                break;
            case EnvironmentStackItem::ItemKind::HeapPointer:
                Flag = Element.Value.HeapPointerVal;
                break;
            case EnvironmentStackItem::ItemKind::FunctionPointer:
                Flag = Element.Value.FuncPointerVal;
                break;
            case EnvironmentStackItem::ItemKind::Null:
                Flag = false;
                break;
        }

        if (!Flag) {
            InterpreterEnvironment.ProgramCounter.NowIndex += Param.IntValue - 1;
        }
    }

    void BytecodeInterpreter::InstructionPCJump(BytecodeStructure::InstructionParam Param) {
        InterpreterEnvironment.ProgramCounter.NowIndex += Param.IntValue - 1;
    }

    void BytecodeInterpreter::InstructionFuncInvoke(BytecodeStructure::InstructionParam Param) {
        /* get function address */
        EnvironmentStackItem Item = InterpreterEnvironment.Stack.PopValueFromStack();
        /* invoke <params count> */
        InterpreterEnvironment.Stack.FramesInformation.back().Length -= Param.HeapPointerValue;
        InterpreterEnvironment.Stack.FramesInformation.push_back(
                {EnvironmentStackFramesInformation::FrameKind::FunctionStackFrame,
                 InterpreterEnvironment.Stack.FramesInformation.back().From +
                 InterpreterEnvironment.Stack.FramesInformation.back().Length,
                 Param.HeapPointerValue,
                 InterpreterEnvironment.ProgramCounter
                });
        switch (Item.Kind) {
            case EnvironmentStackItem::ItemKind::FunctionPointer: {
                InterpreterEnvironment.ProgramCounter = (ProgramCounterInformation) {
                        Item.Value.FuncPointerVal->BytecodeArray,
                        Item.Value.FuncPointerVal->PackageID};

                // Fix bugs
                InterpreterEnvironment.ProgramCounter.NowIndex -= 1;
                break;
            }
            case EnvironmentStackItem::ItemKind::NativeMethodPointer: {
                /* 被调用者需要手动调整栈帧 */
                Item.Value.NativeMethodPointerVal->Method(
                        {(void *) &InterpreterEnvironment, (void *) &GC, Param.HeapPointerValue});
                break;
            }
            default: {
                throw BytecodeInterpretError(L"Expected a FunctionPointer or NativeMethodPointer.");
            }
        }
    }

    void BytecodeInterpreter::InstructionFuncReturn(BytecodeStructure::InstructionParam Param) {
        GC.Start();
        /**
         * 保存结果
         */
        auto Element = InterpreterEnvironment.Stack.PopValueFromStack();

        /**
         * 调整栈帧
         */
        XIndexType S = InterpreterEnvironment.Stack.FramesInformation.back().Length;
        while (S--) {
            InterpreterEnvironment.Stack.PopValueFromStack();
        }
        InterpreterEnvironment.ProgramCounter = InterpreterEnvironment.Stack.FramesInformation.back().ReturnAddress;
        InterpreterEnvironment.Stack.FramesInformation.pop_back();

        /**
         * 压入结果
         */
        InterpreterEnvironment.Stack.PushValueToStack(Element);

        /* 不需要调整ProgramCounter, 进入Invoke下一条指令 */
    }

    void BytecodeInterpreter::InstructionStaticGet(BytecodeStructure::InstructionParam Param) {
        InterpreterEnvironment.Stack.PushValueToStack(
                InterpreterEnvironment.Packages[InterpreterEnvironment.ProgramCounter.Package].GetStatic(
                        Param.HeapPointerValue));
    }

    void BytecodeInterpreter::InstructionStackPushFunction(BytecodeStructure::InstructionParam Param) {
        InterpreterEnvironment.Stack.PushValueToStack(
                (EnvironmentStackItem) {EnvironmentStackItem::ItemKind::FunctionPointer,
                                        (EnvironmentStackItem::ItemValue) &InterpreterEnvironment.Packages[InterpreterEnvironment.ProgramCounter.Package].FunctionPool[Param.HeapPointerValue]});
    }

    void BytecodeInterpreter::InstructionClassNew(BytecodeStructure::InstructionParam Param) {
        GC.Start();
        if (InterpreterEnvironment.Packages[InterpreterEnvironment.ProgramCounter.Package].ClassTemplates.count(
                Param.HeapPointerValue)) {
            const auto &Template = InterpreterEnvironment.Packages[InterpreterEnvironment.ProgramCounter.Package].ClassTemplates[Param.HeapPointerValue];
            EnvClassObject *Object = NewEnvClassObject();
            Object->Parent = Template.Parent;
            // initialize parent
            if (Object->Parent.ClassID) {
                auto ParentTemplate = InterpreterEnvironment.Packages[Object->Parent.PackageID].ClassTemplates[Object->Parent.ClassID];
                InstructionPCGetCurrentPackageID((BytecodeStructure::InstructionParam) {(XIndexType) {}});
                InstructionPCSetCurrentPackageID((BytecodeStructure::InstructionParam) {Object->Parent.PackageID});
                InstructionClassNew((BytecodeStructure::InstructionParam) {Object->Parent.ClassID});
                InstructionPCRestorePackageID((BytecodeStructure::InstructionParam) {(XIndexType) {}});

                Object->Members[Hash(L"super")] = InterpreterEnvironment.Stack.PopValueFromStack().Value.HeapPointerVal;
            }
            // initialize itself
            for (auto &I: Template.Methods) {
                EnvObject MethodPointer{EnvObject::ObjectKind::FunctionPointer,
                                        (EnvObject::ObjectValue) {
                                                &InterpreterEnvironment.Packages[InterpreterEnvironment.ProgramCounter.Package].FunctionPool[I.second]}};
                XHeapIndexType Idx = InterpreterEnvironment.Heap.PushElement(MethodPointer);
                Object->Members.insert({I.first, Idx});
            }
            XHeapIndexType ClassPointer = InterpreterEnvironment.Heap.PushElement({EnvObject::ObjectKind::ClassObject,
                                                                                   (EnvObject::ObjectValue) {Object}});
            InterpreterEnvironment.Stack.PushValueToStack(
                    (EnvironmentStackItem) {EnvironmentStackItem::ItemKind::HeapPointer,
                                            (EnvironmentStackItem::ItemValue) {ClassPointer}});
            return;
        } else {
            throw BytecodeInterpretError(L"BytecodeInterpreter::InstructionClassNew(): class does not exist.");
        }
    }

    void BytecodeInterpreter::InstructionClassGetMember(BytecodeStructure::InstructionParam Param) {
        EnvironmentStackItem Item = InterpreterEnvironment.Stack.PopValueFromStack();
        auto *ClassPointer =
                InterpreterEnvironment.Heap.HeapData[Item.Value.HeapPointerVal].Value.ClassObjectPointer;
        InterpreterEnvironment.Stack.PushValueToStack(
                (EnvironmentStackItem) {EnvironmentStackItem::ItemKind::HeapPointer,
                                        (EnvironmentStackItem::ItemValue) {
                                                ClassPointer->GetMember(Param.HeapPointerValue)}});
    }

    void BytecodeInterpreter::InstructionClassNewMember(BytecodeStructure::InstructionParam Param) {
        GC.Start();
        EnvironmentStackItem Item = InterpreterEnvironment.Stack.PopValueFromStack();
        auto *ClassPointer =
                InterpreterEnvironment.Heap.HeapData[Item.Value.HeapPointerVal].Value.ClassObjectPointer;
        EnvObject Object{EnvObject::ObjectKind::Integer, (EnvObject::ObjectValue) {(XInteger) {0}}};
        ClassPointer->Members[Param.HeapPointerValue] = InterpreterEnvironment.Heap.PushElement(Object);
    }

    void BytecodeInterpreter::InstructionListRemoveIndex(BytecodeStructure::InstructionParam Param) {

    }

    void BytecodeInterpreter::InstructionPCGetCurrentPackageID(BytecodeStructure::InstructionParam Param) {
        InterpreterEnvironment.Stack.PushValueToStack(
                (EnvironmentStackItem) {EnvironmentStackItem::ItemKind::Null,
                                        (EnvironmentStackItem::ItemValue) InterpreterEnvironment.ProgramCounter.Package});
    }

    void BytecodeInterpreter::InstructionPCSetCurrentPackageID(BytecodeStructure::InstructionParam Param) {
        InterpreterEnvironment.ProgramCounter.Package = Param.HeapPointerValue;
    }

    void BytecodeInterpreter::InstructionPCRestorePackageID(BytecodeStructure::InstructionParam Param) {
        EnvironmentStackItem Item = InterpreterEnvironment.Stack.PopValueFromStack();
        EnvironmentStackItem PkgID = InterpreterEnvironment.Stack.PopValueFromStack();
        InterpreterEnvironment.Stack.PushValueToStack(Item);
        InterpreterEnvironment.ProgramCounter.Package = PkgID.Value.HeapPointerVal;
    }

    void BytecodeInterpreter::ConstructNativeClass(XIndexType HashOfPath) {
        if (InterpreterEnvironment.NativeLibraries.IsLoaded(HashOfPath)) {
            EnvClassObject *Object = NewEnvClassObject();

            Object->Members[Hash(L"__native_library_identifier__")] = InterpreterEnvironment.Heap.PushElement(
                    {EnvObject::ObjectKind::Index, (EnvObject::ObjectValue) {HashOfPath}});

            /* Because the address of each element in LoadedLibraries are static after initialized, we can use pointer to this address without any worried. */
            for (auto &I: InterpreterEnvironment.NativeLibraries[HashOfPath].Information.Methods) {
                Object->Members[I.first] = InterpreterEnvironment.Heap.PushElement(
                        {EnvObject::ObjectKind::NativeMethodPointer, (EnvObject::ObjectValue) {&I.second}});
            }
            InterpreterEnvironment.Stack.PushValueToStack(
                    (EnvironmentStackItem) {EnvironmentStackItem::ItemKind::HeapPointer,
                                            (EnvironmentStackItem::ItemValue) {
                                                    InterpreterEnvironment.Heap.PushElement(
                                                            {EnvObject::ObjectKind::ClassObject,
                                                             (EnvObject::ObjectValue) {Object}})
                                            }});
        }
    }

    void BytecodeInterpreter::InstructionNativeClassNew(BytecodeStructure::InstructionParam param) {
        GC.Start();
        ConstructNativeClass(param.HeapPointerValue);
    }

    void BytecodeInterpreter::InstructionExceptionPush(BytecodeStructure::InstructionParam Param) {
        ExceptionTableItem Item;
        Item.CatchBlockOffset = Param.HeapPointerValue;
        Item.ExceptionRegisterCommandPosition = InterpreterEnvironment.ProgramCounter.NowIndex;
        Item.StackItemCnt = InterpreterEnvironment.Stack.Elements.size();
        InterpreterEnvironment.RuntimeExceptionTable.push_back(Item);
    }

    void BytecodeInterpreter::InstructionExceptionPop(BytecodeStructure::InstructionParam Param) {
        InterpreterEnvironment.RuntimeExceptionTable.pop_back();
    }

    void BytecodeInterpreter::InstructionExceptionThrow(BytecodeStructure::InstructionParam Param) {
        if (InterpreterEnvironment.RuntimeExceptionTable.empty()) {

        } else {
            ExceptionTableItem Ex = InterpreterEnvironment.RuntimeExceptionTable.back();
            InterpreterEnvironment.RuntimeExceptionTable.pop_back();
            EnvironmentStackItem threwValue = InterpreterEnvironment.Stack.PopValueFromStack();
            XIndexType FrameIdx = 0;

            // 回退棧幀
            for (auto &Frame : InterpreterEnvironment.Stack.FramesInformation) {
                if (Frame.From > Ex.StackItemCnt) {
                    break;
                }
                FrameIdx++;
            }
            while (InterpreterEnvironment.Stack.FramesInformation.size() > FrameIdx) {
                while (InterpreterEnvironment.Stack.FramesInformation.back().Length--)
                    InterpreterEnvironment.Stack.Elements.pop_back();

                InterpreterEnvironment.ProgramCounter = InterpreterEnvironment.Stack.FramesInformation.back().ReturnAddress;
            }
            while (Ex.StackItemCnt > InterpreterEnvironment.Stack.Elements.size()) {
                InterpreterEnvironment.Stack.Elements.pop_back();
            }

            // 將Exception壓入棧
            InterpreterEnvironment.Stack.PushValueToStack(threwValue);


            // 定位catch
            InterpreterEnvironment.ProgramCounter.NowIndex = Ex.ExceptionRegisterCommandPosition + Ex.CatchBlockOffset - 1;
        }
    }
} // XScript