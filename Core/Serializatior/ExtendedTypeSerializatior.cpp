//
// Created by Jerry Chou on 2022/5/31.
//

#include <algorithm>
#include "ExtendedTypeSerializatior.hpp"
#include "BaseTypeSerializatior.hpp"
#include "../../Share/Exceptions/InternalException.hpp"

namespace XScript {
    namespace Serializatior {
        ExtendedTypeSerializatior::ExtendedTypeSerializatior() {

        }

        void ExtendedTypeSerializatior::operator()(FILE *FilePointer, BytecodeStructure Instruction) {
            BaseTypeSerializatior()(FilePointer, static_cast<XInteger>(Instruction.Instruction));
            ExtendedTypeSerializatior()(FilePointer, Instruction.Param);
        }

        void ExtendedTypeSerializatior::operator()(FILE *FilePointer, BytecodeStructure::InstructionParam Param) {
            if (fwrite(&Param, sizeof(Param), 1, FilePointer) == -1) {
                throw InternalException(L"ExtendedTypeSerializatior: Cannot write to file.");
            }
        }

        void ExtendedTypeSerializatior::operator()(FILE *FilePointer, const XArray<BytecodeStructure> &Instruction) {
            XIndexType Size = Instruction.size();
            BaseTypeSerializatior()(FilePointer, Size);
            for (auto &Item: Instruction) {
                ExtendedTypeSerializatior()(FilePointer, Item);
            }
        }

        void ExtendedTypeSerializatior::operator()(FILE *FilePointer, const Compiler::CompilingTimeFunction &Function) {
            ExtendedTypeSerializatior()(FilePointer, Function.Descriptors);
            ExtendedTypeSerializatior()(FilePointer, Function.BytecodeArray);
        }

        void ExtendedTypeSerializatior::operator()(FILE *FilePointer, const XArray<XString> &Strings) {
            XIndexType Size = Strings.size();
            BaseTypeSerializatior()(FilePointer, Size);
            for (auto &Item: Strings) {
                BaseTypeSerializatior()(FilePointer, Item);
            }
        }

        void
        ExtendedTypeSerializatior::operator()(FILE *FilePointer, Compiler::CompilingTimeFunction::Descriptor Desc) {
            if (fwrite(&Desc, sizeof(Desc), 1, FilePointer) == -1) {
                throw InternalException(L"ExtendedTypeSerializatior: Cannot write to file.");
            }
        }

        void ExtendedTypeSerializatior::operator()(FILE *FilePointer,
                                                   const XArray<Compiler::CompilingTimeFunction::Descriptor> &Descriptors) {
            XIndexType Size = Descriptors.size();
            BaseTypeSerializatior()(FilePointer, Size);
            for (auto &Item: Descriptors) {
                ExtendedTypeSerializatior()(FilePointer, Item);
            }
        }

        void ExtendedTypeSerializatior::operator()(FILE *FilePointer, const XArray<XIndexType> &Strings) {
            XIndexType Size = Strings.size();
            BaseTypeSerializatior()(FilePointer, Size);
            for (auto &Item: Strings) {
                BaseTypeSerializatior()(FilePointer, Item);
            }
        }

        void ExtendedTypeSerializatior::operator()(FILE *FilePointer, const Compiler::CompilingTimeClass &Class) {
            XArray<XIndexType> Constructors;
            XArray<XIndexType> Methods;

            for (auto &Method: Class.Methods) {
                Constructors.push_back(Hash(Method));
            }

            ExtendedTypeSerializatior()(FilePointer, Class.ParentClasses);
            ExtendedTypeSerializatior()(FilePointer, Methods);
        }

        void ExtendedTypeSerializatior::operator()(FILE *FilePointer, const Compiler::ConstantPool &Pool) {
            XIndexType Length = Pool.Items.size();
            BaseTypeSerializatior()(FilePointer, Length);

            for (auto &Item: Pool.Items) {
                ExtendedTypeSerializatior()(FilePointer, Item);
            }
        }

        void
        ExtendedTypeSerializatior::operator()(FILE *FilePointer, const Compiler::ConstantPool::ItemStructure &Item) {
            BaseTypeSerializatior()(FilePointer, static_cast<XInteger>(Item.Kind));
            BaseTypeSerializatior()(FilePointer, Item.StrVal);

        }

        void ExtendedTypeSerializatior::operator()(FILE *FilePointer,
                                                   const Compiler::CompilingTimePackageStructure &Package) {
            ExtendedTypeSerializatior()(FilePointer, Package.Constants);

            XIndexType FuncArrLength = Package.Functions.size();
            BaseTypeSerializatior()(FilePointer, FuncArrLength);

            for (auto &Item: Package.Functions) {
                BaseTypeSerializatior()(FilePointer, Item.first);
                ExtendedTypeSerializatior()(FilePointer, Item.second);
            }

            ExtendedTypeSerializatior()(FilePointer, Package.PackageInitializeCodes);

            BaseTypeSerializatior()(FilePointer, static_cast<XIndexType>(Package.Statics.size()));
        }
    } // XScript
} // Serializatior