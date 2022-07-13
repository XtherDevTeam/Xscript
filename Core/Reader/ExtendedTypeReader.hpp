//
// Created by Jerry Chou on 2022/7/9.
//

#ifndef XSCRIPT2_EXTENDEDTYPEREADER_HPP
#define XSCRIPT2_EXTENDEDTYPEREADER_HPP

#include "../../Executor/BytecodeStructure.hpp"
#include "../../Executor/EnvFunction.hpp"
#include "../../Executor/EnvConstantPool.hpp"
#include "../../Executor/EnvPackageStructure.hpp"
#include "../../Executor/Environment.hpp"
#include "../../Backend/CompilingTimeFunction.hpp"
#include "../../Backend/CompilingTimePackageStructure.hpp"

namespace XScript {
    namespace Reader {

        class ExtendedTypeReader {
        public:
            ExtendedTypeReader();

            BytecodeStructure::InstructionParam ReadInstructionParam(FILE *FilePointer);

            BytecodeStructure ReadInstruction(FILE *FilePointer);

            XArray<BytecodeStructure> ReadInstructionArray(FILE *FilePointer);

            XArray<XString> ReadStringArray(FILE *FilePointer);

            XArray<XIndexType> ReadIndexArray(FILE *FilePointer);

            EnvFunction ReadFunction(FILE *FilePointer);

            XArray<EnvFunction> ReadFunctionArray(FILE *FilePointer);

            EnvConstantPool::EnvConstant ReadConstant(FILE *FilePointer);

            EnvConstantPool ReadConstants(FILE *FilePointer);

            EnvPackageStructure ReadPackage(FILE *FilePointer);

            Compiler::CompilingTimeFunction ReadFunctionEx(FILE *FilePointer);

            XArray<Compiler::CompilingTimeFunction> ReadFunctionArrayEx(FILE *FilePointer);

            Compiler::ConstantPool::ItemStructure ReadConstantEx(FILE *FilePointer);

            Compiler::ConstantPool ReadConstantsEx(FILE *FilePointer);

            Compiler::CompilingTimePackageStructure ReadPackageEx(FILE *FilePointer);
        };

    } // XScript
} // Reader

#endif //XSCRIPT2_EXTENDEDTYPEREADER_HPP
