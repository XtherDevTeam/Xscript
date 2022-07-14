//
// Created by Jerry Chou on 2022/5/14.
//

#ifndef XSCRIPT2_BYTECODEINTERPRETER_HPP
#define XSCRIPT2_BYTECODEINTERPRETER_HPP

#include "Environment.hpp"
#include "../Share/Exceptions/BytecodeInterpretError.hpp"

namespace XScript {

    class BytecodeInterpreter {
    public:
        Environment &InterpreterEnvironment;

        explicit BytecodeInterpreter(Environment &interpreterEnvironment);

        void MainLoop();

        void InstructionCalculationAdd(BytecodeStructure::InstructionParam Param);

        void InstructionCalculationSub(BytecodeStructure::InstructionParam Param);

        void InstructionCalculationMul(BytecodeStructure::InstructionParam Param);

        void InstructionCalculationDiv(BytecodeStructure::InstructionParam Param);

        void InstructionCalculationMod(BytecodeStructure::InstructionParam Param);

        void InstructionLogicAnd(BytecodeStructure::InstructionParam Param);

        void InstructionLogicOr(BytecodeStructure::InstructionParam Param);

        void InstructionLogicEqual(BytecodeStructure::InstructionParam Param);

        void InstructionLogicNotEqual(BytecodeStructure::InstructionParam Param);

        void InstructionLogicGreatEqual(BytecodeStructure::InstructionParam Param);

        void InstructionLogicLessEqual(BytecodeStructure::InstructionParam Param);

        void InstructionLogicGreat(BytecodeStructure::InstructionParam Param);

        void InstructionLogicLess(BytecodeStructure::InstructionParam Param);

        void InstructionBinaryAnd(BytecodeStructure::InstructionParam Param);

        void InstructionBinaryOr(BytecodeStructure::InstructionParam Param);

        void InstructionBinaryXOR(BytecodeStructure::InstructionParam Param);

        void InstructionBinaryNot(BytecodeStructure::InstructionParam Param);

        void InstructionBinaryLM(BytecodeStructure::InstructionParam Param);

        void InstructionBinaryRM(BytecodeStructure::InstructionParam Param);

        void InstructionStackPushInteger(BytecodeStructure::InstructionParam Param);

        void InstructionStackPushDecimal(BytecodeStructure::InstructionParam Param);

        void InstructionStackPushBoolean(BytecodeStructure::InstructionParam Param);

        void InstructionStackPushEmpty(BytecodeStructure::InstructionParam Param);

        void InstructionStackPop(BytecodeStructure::InstructionParam Param);

        void InstructionStackDuplicate(BytecodeStructure::InstructionParam Param);

        void InstructionStackStore(BytecodeStructure::InstructionParam Param);

        void InstructionStaticStore(BytecodeStructure::InstructionParam Param);

        void InstructionConstantsLoad(BytecodeStructure::InstructionParam Param);

        void InstructionCalculationNegate(BytecodeStructure::InstructionParam Param);

        void InstructionListNew(BytecodeStructure::InstructionParam Param);

        void InstructionListPop(BytecodeStructure::InstructionParam Param);

        void InstructionListPush(BytecodeStructure::InstructionParam Param);

        void InstructionListGetMember(BytecodeStructure::InstructionParam Param);

        void InstructionObjectStore(BytecodeStructure::InstructionParam Param);

        void InstructionObjectLvalue2Rvalue(BytecodeStructure::InstructionParam Param);

        void InstructionPCJumpIfTrue(BytecodeStructure::InstructionParam Param);

        void InstructionPCJumpIfFalse(BytecodeStructure::InstructionParam Param);

        void InstructionPCJump(BytecodeStructure::InstructionParam Param);

        void InstructionPCGetCurrentPackageID(BytecodeStructure::InstructionParam Param);

        void InstructionPCSetCurrentPackageID(BytecodeStructure::InstructionParam Param);

        void InstructionPCRestorePackageID(BytecodeStructure::InstructionParam Param);

        void InstructionFuncInvoke(BytecodeStructure::InstructionParam Param);

        void InstructionFuncReturn(BytecodeStructure::InstructionParam Param);

        void InstructionStaticGet(BytecodeStructure::InstructionParam param);

        void InstructionStackPushFunction(BytecodeStructure::InstructionParam param);

        void InstructionClassNew(BytecodeStructure::InstructionParam param);

        void InstructionClassGetMember(BytecodeStructure::InstructionParam param);

        void InstructionListRemoveIndex(BytecodeStructure::InstructionParam param);
    };

} // XScript

#endif //XSCRIPT2_BYTECODEINTERPRETER_HPP
