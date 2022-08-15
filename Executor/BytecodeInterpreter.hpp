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

        void ConstructNativeClass(XIndexType HashOfPath, XIndexType ClassName) const;
        
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

        void InstructionBinaryAnd(BytecodeStructure::InstructionParam Param) const;

        void InstructionBinaryOr(BytecodeStructure::InstructionParam Param) const;

        void InstructionBinaryXOR(BytecodeStructure::InstructionParam Param) const;

        void InstructionBinaryNot(BytecodeStructure::InstructionParam Param) const;

        void InstructionBinaryLM(BytecodeStructure::InstructionParam Param) const;

        void InstructionBinaryRM(BytecodeStructure::InstructionParam Param) const;

        void InstructionStackPushInteger(BytecodeStructure::InstructionParam Param) const;

        void InstructionStackPushDecimal(BytecodeStructure::InstructionParam Param) const;

        void InstructionStackPushBoolean(BytecodeStructure::InstructionParam Param) const;

        void InstructionStackPushEmpty(BytecodeStructure::InstructionParam Param) const;

        void InstructionStackPop(BytecodeStructure::InstructionParam Param) const;

        void InstructionStackDuplicate(BytecodeStructure::InstructionParam Param) const;

        void InstructionStackGetTop(BytecodeStructure::InstructionParam Param) const;

        void InstructionStackStore(BytecodeStructure::InstructionParam Param) const;

        void InstructionStaticStore(BytecodeStructure::InstructionParam Param) const;

        void InstructionConstantsLoad(BytecodeStructure::InstructionParam Param) const;

        void InstructionCalculationNegate(BytecodeStructure::InstructionParam Param) const;

        void InstructionListNew(BytecodeStructure::InstructionParam Param) const;

        void InstructionListPush(BytecodeStructure::InstructionParam Param) const;

        void InstructionListGetMember(BytecodeStructure::InstructionParam Param);

        void InstructionObjectStore(BytecodeStructure::InstructionParam Param) const;

        void InstructionObjectLvalue2Rvalue(BytecodeStructure::InstructionParam Param) const;

        void InstructionPCJumpIfTrue(BytecodeStructure::InstructionParam Param) const;

        void InstructionPCJumpIfFalse(BytecodeStructure::InstructionParam Param) const;

        void InstructionPCJump(BytecodeStructure::InstructionParam Param) const;

        void InstructionPCGetCurrentPackageID(BytecodeStructure::InstructionParam Param) const;

        void InstructionPCSetCurrentPackageID(BytecodeStructure::InstructionParam Param) const;

        void InstructionPCRestorePackageID(BytecodeStructure::InstructionParam Param) const;

        void InstructionFuncInvoke(BytecodeStructure::InstructionParam Param);

        void InstructionFuncReturn(BytecodeStructure::InstructionParam Param) const;

        void InstructionStaticGet(BytecodeStructure::InstructionParam Param) const;

        void InstructionStackPushFunction(BytecodeStructure::InstructionParam Param) const;

        void InstructionClassNew(BytecodeStructure::InstructionParam Param);

        void InstructionClassGetMember(BytecodeStructure::InstructionParam Param) const;

        void InstructionClassNewMember(BytecodeStructure::InstructionParam Param) const;

        void InstructionClassInstanceOf(BytecodeStructure::InstructionParam Param) const;

        void InstructionListRemoveIndex(BytecodeStructure::InstructionParam Param);

        void InstructionNativeClassNew(BytecodeStructure::InstructionParam Param);

        void InstructionExceptionPush(BytecodeStructure::InstructionParam Param) const;

        void InstructionExceptionPop(BytecodeStructure::InstructionParam Param) const;

        void InstructionExceptionThrow(BytecodeStructure::InstructionParam Param) const;

        void InstructionCreateClosure(BytecodeStructure::InstructionParam Param) const;
    };

} // XScript

#endif //XSCRIPT2_BYTECODEINTERPRETER_HPP
