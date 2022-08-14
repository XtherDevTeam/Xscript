//
// Created by Jerry Chou on 2022/5/14.
//

#ifndef XSCRIPT2_BYTECODEINTERPRETER_HPP
#define XSCRIPT2_BYTECODEINTERPRETER_HPP

#include <mutex>
#include "Environment.hpp"
#include "../Share/Exceptions/BytecodeInterpretError.hpp"
#include "GarbageCollection.hpp"

namespace XScript {
    class BytecodeInterpreter {
    public:
        bool IsBusy;
        XIndexType ThreadID;
        void *Pool{};
        Environment *InterpreterEnvironment;
        GarbageCollection *GC;

        BytecodeInterpreter();

        void MainLoop();

        void ConstructNativeClass(XIndexType HashOfPath, XIndexType ClassName);
        
        void InstructionCalculationAdd(BytecodeStructure::InstructionParam Param);

        void InstructionCalculationSub(BytecodeStructure::InstructionParam Param);

        void InstructionCalculationMul(BytecodeStructure::InstructionParam Param);

        void InstructionCalculationDiv(BytecodeStructure::InstructionParam Param);

        void InstructionCalculationMod(BytecodeStructure::InstructionParam Param);

        void InstructionLogicAnd(BytecodeStructure::InstructionParam Param);

        void InstructionLogicOr(BytecodeStructure::InstructionParam Param);

        void InstructionLogicEqual(BytecodeStructure::InstructionParam Param) const;

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

        void InstructionStackGetTop(BytecodeStructure::InstructionParam Param);

        void InstructionStackStore(BytecodeStructure::InstructionParam Param);

        void InstructionStaticStore(BytecodeStructure::InstructionParam Param);

        void InstructionConstantsLoad(BytecodeStructure::InstructionParam Param);

        void InstructionCalculationNegate(BytecodeStructure::InstructionParam Param);

        void InstructionListNew(BytecodeStructure::InstructionParam Param);

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

        void InstructionStaticGet(BytecodeStructure::InstructionParam Param);

        void InstructionStackPushFunction(BytecodeStructure::InstructionParam Param);

        void InstructionClassNew(BytecodeStructure::InstructionParam Param);

        void InstructionClassGetMember(BytecodeStructure::InstructionParam Param);

        void InstructionClassNewMember(BytecodeStructure::InstructionParam Param);

        void InstructionClassInstanceOf(BytecodeStructure::InstructionParam Param);

        void InstructionListRemoveIndex(BytecodeStructure::InstructionParam Param);

        void InstructionNativeClassNew(BytecodeStructure::InstructionParam Param);

        void InstructionExceptionPush(BytecodeStructure::InstructionParam Param);

        void InstructionExceptionPop(BytecodeStructure::InstructionParam Param);

        void InstructionExceptionThrow(BytecodeStructure::InstructionParam Param);

        void InstructionCreateClosure(BytecodeStructure::InstructionParam Param);
    };

} // XScript

#endif //XSCRIPT2_BYTECODEINTERPRETER_HPP
