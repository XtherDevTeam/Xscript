//
// Created by Jerry Chou on 2022/5/14.
//

//#include <iostream>
#include "BytecodeInterpreter.hpp"

namespace XScript {
    BytecodeInterpreter::BytecodeInterpreter(Environment &interpreterEnvironment) : InterpreterEnvironment(
            interpreterEnvironment) {}

    void BytecodeInterpreter::MainLoop() {
        while (InterpreterEnvironment.ProgramCounter.NowIndex !=
               InterpreterEnvironment.ProgramCounter.Pointer->size()) {
            auto CurrentInstruction = (*InterpreterEnvironment.ProgramCounter.Pointer)[InterpreterEnvironment.ProgramCounter.NowIndex];
            /* process commands */
//            std::cout << "VMInstruction: " << wstring2string(CurrentInstruction.ToString()) << std::endl;

            switch (CurrentInstruction.Instruction) {
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
                case BytecodeStructure::InstructionEnum::logic_and: {
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
                        case EnvironmentStackItem::ItemKind::HeapPointer:
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
                    break;
                }
                case BytecodeStructure::InstructionEnum::logic_or: {
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
                        case EnvironmentStackItem::ItemKind::HeapPointer:
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
                    break;
                }
                case BytecodeStructure::InstructionEnum::logic_equal: {
                    auto Right = InterpreterEnvironment.Stack.PopValueFromStack();
                    auto Left = InterpreterEnvironment.Stack.PopValueFromStack();
                    bool Result = false;

                    if (Left.Kind == Right.Kind) {
                        switch (Left.Kind) {
                            case EnvironmentStackItem::ItemKind::Integer:
                            case EnvironmentStackItem::ItemKind::Decimal:
                            case EnvironmentStackItem::ItemKind::Boolean:
                            case EnvironmentStackItem::ItemKind::Null:
                                Result = Left.Value.IntVal == Right.Value.IntVal;
                                break;
                            case EnvironmentStackItem::ItemKind::HeapPointer:
                                Result = InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal] ==
                                         InterpreterEnvironment.Heap.HeapData[Right.Value.HeapPointerVal];
                                break;
                        }
                    }
                    InterpreterEnvironment.Stack.PushValueToStack(
                            {EnvironmentStackItem::ItemKind::Boolean, (EnvironmentStackItem::ItemValue) {Result}});
                    break;
                }
                case BytecodeStructure::InstructionEnum::logic_not_equal: {
                    auto Right = InterpreterEnvironment.Stack.PopValueFromStack();
                    auto Left = InterpreterEnvironment.Stack.PopValueFromStack();
                    bool Result = false;

                    if (Left.Kind == Right.Kind) {
                        switch (Left.Kind) {
                            case EnvironmentStackItem::ItemKind::Integer:
                            case EnvironmentStackItem::ItemKind::Decimal:
                            case EnvironmentStackItem::ItemKind::Boolean:
                            case EnvironmentStackItem::ItemKind::Null:
                                Result = Left.Value.IntVal != Right.Value.IntVal;
                                break;
                            case EnvironmentStackItem::ItemKind::HeapPointer:
                                Result = InterpreterEnvironment.Heap.HeapData[Left.Value.HeapPointerVal] !=
                                         InterpreterEnvironment.Heap.HeapData[Right.Value.HeapPointerVal];
                                break;
                        }
                    }
                    InterpreterEnvironment.Stack.PushValueToStack(
                            {EnvironmentStackItem::ItemKind::Boolean, (EnvironmentStackItem::ItemValue) {Result}});
                    break;
                }
                case BytecodeStructure::InstructionEnum::logic_great_equal: {
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
                                case EnvironmentStackItem::ItemKind::HeapPointer:
                                    /* TODO: Add classes to XScript 2 */
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
                                case EnvironmentStackItem::ItemKind::HeapPointer:
                                    /* TODO: Add classes to XScript 2*/
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
                                case EnvironmentStackItem::ItemKind::HeapPointer:
                                    throw BytecodeInterpretError(L"Cannot compare integers with a object.");
                                case EnvironmentStackItem::ItemKind::Null:
                                    throw BytecodeInterpretError(L"Cannot compare with a null value.");
                            }
                            InterpreterEnvironment.Stack.PushValueToStack({EnvironmentStackItem::ItemKind::Boolean,
                                                                           (EnvironmentStackItem::ItemValue) {Result}});
                            break;
                        case EnvironmentStackItem::ItemKind::HeapPointer:
                            /* TODO: Add classes to XScript 2 */
                            break;
                        case EnvironmentStackItem::ItemKind::Null:
                            throw BytecodeInterpretError(L"Cannot add elements with a null value.");
                    }
                    break;
                }
                case BytecodeStructure::InstructionEnum::logic_less_equal: {
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
                                case EnvironmentStackItem::ItemKind::HeapPointer:
                                    /* TODO: Add classes to XScript 2 */
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
                                case EnvironmentStackItem::ItemKind::HeapPointer:
                                    /* TODO: Add classes to XScript 2*/
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
                                case EnvironmentStackItem::ItemKind::HeapPointer:
                                    throw BytecodeInterpretError(L"Cannot compare integers with a object.");
                                case EnvironmentStackItem::ItemKind::Null:
                                    throw BytecodeInterpretError(L"Cannot compare with a null value.");
                            }
                            InterpreterEnvironment.Stack.PushValueToStack({EnvironmentStackItem::ItemKind::Boolean,
                                                                           (EnvironmentStackItem::ItemValue) {Result}});
                            break;
                        case EnvironmentStackItem::ItemKind::HeapPointer:
                            /* TODO: Add classes to XScript 2 */
                            break;
                        case EnvironmentStackItem::ItemKind::Null:
                            throw BytecodeInterpretError(L"Cannot add elements with a null value.");
                    }
                    break;
                }
                case BytecodeStructure::InstructionEnum::logic_great: {
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
                                case EnvironmentStackItem::ItemKind::HeapPointer:
                                    /* TODO: Add classes to XScript 2 */
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
                                case EnvironmentStackItem::ItemKind::HeapPointer:
                                    /* TODO: Add classes to XScript 2*/
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
                                case EnvironmentStackItem::ItemKind::HeapPointer:
                                    throw BytecodeInterpretError(L"Cannot compare integers with a object.");
                                case EnvironmentStackItem::ItemKind::Null:
                                    throw BytecodeInterpretError(L"Cannot compare with a null value.");
                            }
                            InterpreterEnvironment.Stack.PushValueToStack({EnvironmentStackItem::ItemKind::Boolean,
                                                                           (EnvironmentStackItem::ItemValue) {Result}});
                            break;
                        case EnvironmentStackItem::ItemKind::HeapPointer:
                            /* TODO: Add classes to XScript 2 */
                            break;
                        case EnvironmentStackItem::ItemKind::Null:
                            throw BytecodeInterpretError(L"Cannot add elements with a null value.");
                    }
                    break;
                }
                case BytecodeStructure::InstructionEnum::logic_less: {
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
                                case EnvironmentStackItem::ItemKind::HeapPointer:
                                    /* TODO: Add classes to XScript 2 */
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
                                case EnvironmentStackItem::ItemKind::HeapPointer:
                                    /* TODO: Add classes to XScript 2*/
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
                                case EnvironmentStackItem::ItemKind::HeapPointer:
                                    throw BytecodeInterpretError(L"Cannot compare integers with a object.");
                                case EnvironmentStackItem::ItemKind::Null:
                                    throw BytecodeInterpretError(L"Cannot compare with a null value.");
                            }
                            InterpreterEnvironment.Stack.PushValueToStack({EnvironmentStackItem::ItemKind::Boolean,
                                                                           (EnvironmentStackItem::ItemValue) {Result}});
                            break;
                        case EnvironmentStackItem::ItemKind::HeapPointer:
                            /* TODO: Add classes to XScript 2 */
                            break;
                        case EnvironmentStackItem::ItemKind::Null:
                            throw BytecodeInterpretError(L"Cannot add elements with a null value.");
                    }
                    break;
                }
                case BytecodeStructure::InstructionEnum::binary_and: {
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

                    break;
                }
                case BytecodeStructure::InstructionEnum::binary_or: {
                    /* get two operands from the stack */
                    auto Right = InterpreterEnvironment.Stack.PopValueFromStack();
                    auto Left = InterpreterEnvironment.Stack.PopValueFromStack();

                    if (Right.Kind != EnvironmentStackItem::ItemKind::HeapPointer and
                        Right.Kind != EnvironmentStackItem::ItemKind::Null and
                        Left.Kind != EnvironmentStackItem::ItemKind::HeapPointer and
                        Left.Kind != EnvironmentStackItem::ItemKind::Null) {
                        Left.Value.IntVal = Left.Value.IntVal | Right.Value.IntVal;
                    } else {
                        throw BytecodeInterpretError(L"binary_and: unexpected operands");
                    }
                    InterpreterEnvironment.Stack.PushValueToStack(Left);

                    break;
                }
                case BytecodeStructure::InstructionEnum::binary_xor: {
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

                    break;
                }
                case BytecodeStructure::InstructionEnum::binary_not: {
                    /* get operand from the stack */
                    auto Left = InterpreterEnvironment.Stack.PopValueFromStack();

                    if (Left.Kind != EnvironmentStackItem::ItemKind::HeapPointer and
                        Left.Kind != EnvironmentStackItem::ItemKind::Null) {
                        Left.Value.IntVal = !Left.Value.IntVal;
                    } else {
                        throw BytecodeInterpretError(L"binary_and: unexpected operands");
                    }
                    InterpreterEnvironment.Stack.PushValueToStack(Left);

                    break;
                }
                case BytecodeStructure::InstructionEnum::stack_push_integer: {
                    InterpreterEnvironment.Stack.PushValueToStack({EnvironmentStackItem::ItemKind::Integer,
                                                                   (EnvironmentStackItem::ItemValue) {
                                                                           CurrentInstruction.Param.IntValue}});
                    break;
                }
                case BytecodeStructure::InstructionEnum::stack_push_decimal: {
                    InterpreterEnvironment.Stack.PushValueToStack({EnvironmentStackItem::ItemKind::Decimal,
                                                                   (EnvironmentStackItem::ItemValue) {
                                                                           CurrentInstruction.Param.DeciValue}});
                    break;
                }
                case BytecodeStructure::InstructionEnum::stack_push_boolean: {
                    InterpreterEnvironment.Stack.PushValueToStack({EnvironmentStackItem::ItemKind::Boolean,
                                                                   (EnvironmentStackItem::ItemValue) {
                                                                           CurrentInstruction.Param.BoolValue}});
                    break;
                }
                case BytecodeStructure::InstructionEnum::stack_push_empty: {
                    InterpreterEnvironment.Stack.PushValueToStack({EnvironmentStackItem::ItemKind::Null,
                                                                   (EnvironmentStackItem::ItemValue) {(XIndexType) 0}});
                    break;
                }
                case BytecodeStructure::InstructionEnum::stack_pop: {
                    InterpreterEnvironment.Stack.PopValueFromStack();
                    break;
                }
                case BytecodeStructure::InstructionEnum::stack_duplicate: {
                    /* TODO: Complete the stack frames implementation */
                    EnvironmentStackItem Element = InterpreterEnvironment.Stack.GetValueFromStack(
                            CurrentInstruction.Param.HeapPointerValue);
                    InterpreterEnvironment.Stack.PushValueToStack(Element);
                    break;
                }
                case BytecodeStructure::InstructionEnum::stack_store: {
                    EnvironmentStackItem Element = InterpreterEnvironment.Stack.PopValueFromStack();
                    InterpreterEnvironment.Stack.StoreValueToIndex(CurrentInstruction.Param.HeapPointerValue, Element);
                    break;
                }
                case BytecodeStructure::InstructionEnum::static_store: {
                    EnvironmentStackItem Element = InterpreterEnvironment.Stack.PopValueFromStack();
                    /* TODO: Add packages to XScript2 */
                    break;
                }

                case BytecodeStructure::InstructionEnum::constants_load:
                    break;
                case BytecodeStructure::InstructionEnum::calculation_negate: {
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
                        case EnvironmentStackItem::ItemKind::HeapPointer:
                        case EnvironmentStackItem::ItemKind::Null:
                            throw BytecodeInterpretError(L"calculation_negate: Unexpected input.");
                    }
                    InterpreterEnvironment.Stack.PushValueToStack(Element);
                    break;
                }

                case BytecodeStructure::InstructionEnum::calculation_increment:
                    break;
                case BytecodeStructure::InstructionEnum::calculation_decrement:
                    break;

                case BytecodeStructure::InstructionEnum::list_new: {
                    EnvironmentStackItem ListItem{};
                    ListItem.Kind = EnvironmentStackItem::ItemKind::HeapPointer;
                    ListItem.Value.HeapPointerVal = InterpreterEnvironment.Heap.PushElement(
                            (EnvObject) {EnvObject::ObjectKind::ArrayObject,
                                         (EnvObject::ObjectValue) {NewEnvArrayObject(
                                                 CurrentInstruction.Param.HeapPointerValue)}});
                    for (XIndexType I = 0; I < CurrentInstruction.Param.HeapPointerValue; I++) {
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
                            case EnvironmentStackItem::ItemKind::HeapPointer:
                                Object = InterpreterEnvironment.Heap.HeapData[Item.Value.HeapPointerVal];
                                break;
                            case EnvironmentStackItem::ItemKind::Null:
                                Object.Kind = EnvObject::ObjectKind::Integer;
                                break;
                        }

                        InterpreterEnvironment.Heap.HeapData[ListItem.Value.HeapPointerVal].Value.ArrayObjectPointer->Elements[I] =
                                InterpreterEnvironment.Heap.PushElement(Object);
                    }
                    InterpreterEnvironment.Stack.PushValueToStack(ListItem);
                    break;
                }
                case BytecodeStructure::InstructionEnum::list_pop: {
                    EnvironmentStackItem ListItem = InterpreterEnvironment.Stack.PopValueFromStack();
                    if (ListItem.Kind == EnvironmentStackItem::ItemKind::HeapPointer and
                        InterpreterEnvironment.Heap.HeapData[ListItem.Value.HeapPointerVal].Kind ==
                        EnvObject::ObjectKind::ArrayObject) {
                        InterpreterEnvironment.Heap.HeapData[ListItem.Value.HeapPointerVal].Value.ArrayObjectPointer->Elements.pop_back();
                    }
                    break;
                }
                case BytecodeStructure::InstructionEnum::list_push: {
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
                    break;
                }
                case BytecodeStructure::InstructionEnum::list_get_member: {
                    EnvironmentStackItem ListItem = InterpreterEnvironment.Stack.PopValueFromStack();
                    if (ListItem.Kind == EnvironmentStackItem::ItemKind::HeapPointer and
                        InterpreterEnvironment.Heap.HeapData[ListItem.Value.HeapPointerVal].Kind ==
                        EnvObject::ObjectKind::ArrayObject) {
                        EnvironmentStackItem Index = InterpreterEnvironment.Stack.PopValueFromStack();
                        /* 不做类型检查 */
                        EnvironmentStackItem Item{EnvironmentStackItem::ItemKind::HeapPointer,
                                                  (EnvironmentStackItem::ItemValue) {
                                                          InterpreterEnvironment.Heap.HeapData[ListItem.Value.HeapPointerVal].Value.ArrayObjectPointer->Elements[Index.Value.IntVal]}};

                        InterpreterEnvironment.Stack.PushValueToStack(Item);
                    } else {
                        throw BytecodeInterpretError(L"list_get_member: Unknown item type");
                    }
                    break;
                }

                case BytecodeStructure::InstructionEnum::object_lvalue2rvalue: {
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
                        }

                        /* 如果为基础类型则转换为rvalue，否则保持原状 */
                        InterpreterEnvironment.Stack.PushValueToStack(Item);
                    } else {
                        throw BytecodeInterpretError(L"object_lvalue2rvalue: Unknown item type");
                    }
                }

                case BytecodeStructure::InstructionEnum::pc_jump_if_true: {
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
                        case EnvironmentStackItem::ItemKind::Null:
                            Flag = false;
                            break;
                    }

                    if (Flag) {
                        InterpreterEnvironment.ProgramCounter.NowIndex += CurrentInstruction.Param.IntValue;
                        continue; // 防止NowIndex更新ProgramCounter
                    }
                    break;
                }
                case BytecodeStructure::InstructionEnum::pc_jump_if_false: {
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
                        case EnvironmentStackItem::ItemKind::Null:
                            Flag = false;
                            break;
                    }

                    if (!Flag) {
                        InterpreterEnvironment.ProgramCounter.NowIndex += CurrentInstruction.Param.IntValue;
                        continue; // 防止NowIndex更新ProgramCounter
                    }
                    break;
                }
                case BytecodeStructure::InstructionEnum::pc_jump: {
                    InterpreterEnvironment.ProgramCounter.NowIndex += CurrentInstruction.Param.IntValue;
                    continue; // 防止NowIndex更新ProgramCounter
                }
            }
            InterpreterEnvironment.ProgramCounter.NowIndex++;
        }
    }
} // XScript