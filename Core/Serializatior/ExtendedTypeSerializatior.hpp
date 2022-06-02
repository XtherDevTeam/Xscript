//
// Created by Jerry Chou on 2022/5/31.
//

#ifndef XSCRIPT2_EXTENDEDTYPESERIALIZATIOR_HPP
#define XSCRIPT2_EXTENDEDTYPESERIALIZATIOR_HPP

#include "../../Share/Utils.hpp"
#include "../../Executor/BytecodeStructure.hpp"
#include "../../Backend/CompilingTimeFunction.hpp"
#include "../../Backend/CompilingTimeClass.hpp"

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

            void operator()(FILE *FilePointer, const Compiler::CompilingTimeClass &Class);
        };

    } // XScript
} // Serializatior

#endif //XSCRIPT2_EXTENDEDTYPESERIALIZATIOR_HPP
