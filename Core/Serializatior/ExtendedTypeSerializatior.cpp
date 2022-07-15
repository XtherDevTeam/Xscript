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
            BaseTypeSerializatior()(FilePointer, static_cast<XIndexType>(Function.ArgumentsList.size()));
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
            ExtendedTypeSerializatior()(FilePointer, Class.ParentClasses);

            XIndexType Length = Class.Methods.size();
            BaseTypeSerializatior()(FilePointer, Length);

            for (auto &Method: Class.Methods) {
                BaseTypeSerializatior()(FilePointer, Method.first);
                BaseTypeSerializatior()(FilePointer, Method.second);
            }
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

            ExtendedTypeSerializatior()(FilePointer, Package.Classes);

            XIndexType FuncArrLength = Package.Functions.size();
            BaseTypeSerializatior()(FilePointer, FuncArrLength);

            for (auto &Item: Package.Functions) {
                BaseTypeSerializatior()(FilePointer, Item.first);
                ExtendedTypeSerializatior()(FilePointer, Item.second);
            }

            ExtendedTypeSerializatior()(FilePointer, Package.PackageInitializeCodes);

            BaseTypeSerializatior()(FilePointer, static_cast<XIndexType>(Package.Statics.size()));
            for (auto &Item: Package.Statics) {
                BaseTypeSerializatior()(FilePointer, Item.first);
                BaseTypeSerializatior()(FilePointer, Item.second.IsConstant);
            }
        }

        void ExtendedTypeSerializatior::operator()(FILE *FilePointer, const ClassDescriptor &Class) {
            BaseTypeSerializatior()(FilePointer, Class.PackageID);
            BaseTypeSerializatior()(FilePointer, Class.ClassID);
        }

        void ExtendedTypeSerializatior::operator()(FILE *FilePointer, const XArray<ClassDescriptor> &ClassArr) {
            BaseTypeSerializatior()(FilePointer, static_cast<XIndexType>(ClassArr.size()));
            for (auto &I: ClassArr) {
                ExtendedTypeSerializatior()(FilePointer, I);
            }
        }

        void
        ExtendedTypeSerializatior::operator()(FILE *FilePointer,
                                              const XArray<std::pair<XString, Compiler::CompilingTimeClass>> &Classes) {
            BaseTypeSerializatior()(FilePointer, static_cast<XIndexType>(Classes.size()));
            for (auto &I: Classes) {
                BaseTypeSerializatior()(FilePointer, I.first);
                ExtendedTypeSerializatior()(FilePointer, I.second);
            }
        }
    } // XScript
} // Serializatior