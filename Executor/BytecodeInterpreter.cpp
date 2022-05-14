//
// Created by Jerry Chou on 2022/5/14.
//

#include "BytecodeInterpreter.hpp"

namespace XScript {
    BytecodeInterpreter::BytecodeInterpreter(Environment &interpreterEnvironment) : InterpreterEnvironment(
            interpreterEnvironment) {}

    void BytecodeInterpreter::MainLoop() {
        while (InterpreterEnvironment.ProgramCounter.NowIndex !=
               InterpreterEnvironment.ProgramCounter.Pointer->size()) {
            switch ((*InterpreterEnvironment.ProgramCounter.Pointer)[InterpreterEnvironment.ProgramCounter.NowIndex].Instruction) {
                case BytecodeStructure::InstructionEnum::calculation_add: {
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
                                case EnvironmentStackItem::ItemKind::HeapPointer:
                                    throw BytecodeInterpretError(L"Cannot add integers with a object.");
                                case EnvironmentStackItem::ItemKind::Null:
                                    throw BytecodeInterpretError(L"Cannot add integers with a null value.");
                            }
                            InterpreterEnvironment.Stack.PushValueToStack(Left);
                            break;
                        case EnvironmentStackItem::ItemKind::HeapPointer:
                            break;
                        case EnvironmentStackItem::ItemKind::Null:
                            throw BytecodeInterpretError(L"Cannot add elements with a null value.");
                    }
                    break;
                }
                case BytecodeStructure::InstructionEnum::calculation_sub: {
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
                        case EnvironmentStackItem::ItemKind::HeapPointer:
                            break;
                        case EnvironmentStackItem::ItemKind::Null:
                            throw BytecodeInterpretError(L"Cannot add elements with a null value.");
                    }
                    break;
                }
                case BytecodeStructure::InstructionEnum::calculation_mul: {
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
                                case EnvironmentStackItem::ItemKind::HeapPointer:
                                    throw BytecodeInterpretError(L"Cannot add integers with a object.");
                                case EnvironmentStackItem::ItemKind::Null:
                                    throw BytecodeInterpretError(L"Cannot add integers with a null value.");
                            }
                            InterpreterEnvironment.Stack.PushValueToStack(Left);
                            break;
                        case EnvironmentStackItem::ItemKind::HeapPointer:
                            break;
                        case EnvironmentStackItem::ItemKind::Null:
                            throw BytecodeInterpretError(L"Cannot add elements with a null value.");
                    }
                    break;
                }
                case BytecodeStructure::InstructionEnum::calculation_div: {
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
                                case EnvironmentStackItem::ItemKind::HeapPointer:
                                    throw BytecodeInterpretError(L"Cannot add integers with a object.");
                                case EnvironmentStackItem::ItemKind::Null:
                                    throw BytecodeInterpretError(L"Cannot add integers with a null value.");
                            }
                            InterpreterEnvironment.Stack.PushValueToStack(Left);
                            break;
                        case EnvironmentStackItem::ItemKind::HeapPointer:
                            break;
                        case EnvironmentStackItem::ItemKind::Null:
                            throw BytecodeInterpretError(L"Cannot add elements with a null value.");
                    }
                    break;
                }
                case BytecodeStructure::InstructionEnum::calculation_mod: {
                    auto Right = InterpreterEnvironment.Stack.PopValueFromStack();
                    auto Left = InterpreterEnvironment.Stack.PopValueFromStack();
                    if (Left.Kind != EnvironmentStackItem::ItemKind::Integer or
                        Right.Kind != EnvironmentStackItem::ItemKind::Integer) {
                        throw BytecodeInterpretError(L"Command calculation_mod only can be used between 2 integers.");
                    }
                    Left.Value.IntVal %= Right.Value.IntVal;
                    InterpreterEnvironment.Stack.PushValueToStack(Left);
                    break;
                }
                case BytecodeStructure::InstructionEnum::logic_and:
                    break;
                case BytecodeStructure::InstructionEnum::logic_or:
                    break;
                case BytecodeStructure::InstructionEnum::logic_equal:
                    break;
                case BytecodeStructure::InstructionEnum::logic_not_equal:
                    break;
                case BytecodeStructure::InstructionEnum::logic_great_equal:
                    break;
                case BytecodeStructure::InstructionEnum::logic_less_equal:
                    break;
                case BytecodeStructure::InstructionEnum::logic_great:
                    break;
                case BytecodeStructure::InstructionEnum::logic_less:
                    break;
                case BytecodeStructure::InstructionEnum::binary_and:
                    break;
                case BytecodeStructure::InstructionEnum::binary_or:
                    break;
                case BytecodeStructure::InstructionEnum::binary_xor:
                    break;
                case BytecodeStructure::InstructionEnum::binary_not:
                    break;
                case BytecodeStructure::InstructionEnum::stack_push_integer:
                    break;
                case BytecodeStructure::InstructionEnum::stack_push_decimal:
                    break;
                case BytecodeStructure::InstructionEnum::stack_push_boolean:
                    break;
                case BytecodeStructure::InstructionEnum::stack_push_empty:
                    break;
                case BytecodeStructure::InstructionEnum::stack_pop:
                    break;
                case BytecodeStructure::InstructionEnum::stack_duplicate:
                    break;
                case BytecodeStructure::InstructionEnum::stack_store:
                    break;
                case BytecodeStructure::InstructionEnum::constants_load:
                    break;
            }
        }
    }
} // XScript