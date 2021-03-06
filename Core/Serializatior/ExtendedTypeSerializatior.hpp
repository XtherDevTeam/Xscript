//
// Created by Jerry Chou on 2022/5/31.
//

#ifndef XSCRIPT2_EXTENDEDTYPESERIALIZATIOR_HPP
#define XSCRIPT2_EXTENDEDTYPESERIALIZATIOR_HPP

#include "../../Share/Utils.hpp"
#include "../../Executor/BytecodeStructure.hpp"
#include "../../Backend/CompilingTimeFunction.hpp"
#include "../../Backend/CompilingTimeClass.hpp"
#include "../../Backend/ConstantPool.hpp"
#include "../../Backend/CompilingTimePackageStructure.hpp"

namespace XScript {
    namespace Serializatior {

        class ExtendedTypeSerializatior {
        public:
            ExtendedTypeSerializatior();

            void operator()(FILE *FilePointer, BytecodeStructure::InstructionParam Param);

            void operator()(FILE *FilePointer, BytecodeStructure Instruction);

            void operator()(FILE *FilePointer, const XArray<BytecodeStructure> &Instruction);

            void operator()(FILE *FilePointer, const XArray<XString> &Strings);

            void operator()(FILE *FilePointer, const XArray<XIndexType> &Strings);

            void operator()(FILE *FilePointer, const Compiler::CompilingTimeFunction &Function);

            void operator()(FILE *FilePointer, Compiler::CompilingTimeFunction::Descriptor Desc);

            void operator()(FILE *FilePointer, const XArray<Compiler::CompilingTimeFunction::Descriptor> &Descriptors);

            void operator()(FILE *FilePointer, const ClassDescriptor &Class);

            void operator()(FILE *FilePointer, const XArray<ClassDescriptor> &ClassArr);

            void operator()(FILE *FilePointer, const Compiler::CompilingTimeClass &Class);

            void operator()(FILE *FilePointer, const XArray<std::pair<XString, Compiler::CompilingTimeClass>> &Classes);

            void operator()(FILE *FilePointer, const Compiler::ConstantPool::ItemStructure &Item);

            void operator()(FILE *FilePointer, const Compiler::ConstantPool &Pool);

            void operator()(FILE *FilePointer, const Compiler::CompilingTimePackageStructure &Package);
        };

    } // XScript
} // Serializatior

#endif //XSCRIPT2_EXTENDEDTYPESERIALIZATIOR_HPP
