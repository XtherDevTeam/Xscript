//
// Created by Jerry Chou on 2022/7/9.
//

#include "ExtendedTypeReader.hpp"
#include "BaseTypeReader.hpp"
#include "../../Share/Exceptions/InternalException.hpp"

namespace XScript {
    namespace Reader {
        ExtendedTypeReader::ExtendedTypeReader() {

        }

        BytecodeStructure::InstructionParam ExtendedTypeReader::ReadInstructionParam(FILE *FilePointer) {
            BytecodeStructure::InstructionParam result{static_cast<XIndexType>(0)};
            fread(&result, sizeof(BytecodeStructure::InstructionParam), 1, FilePointer);
            return result;
        }

        BytecodeStructure ExtendedTypeReader::ReadInstruction(FILE *FilePointer) {
            return {static_cast<BytecodeStructure::InstructionEnum>(BaseTypeReader().ReadInteger(FilePointer)),
                    ReadInstructionParam(FilePointer)};
        }

        XArray<BytecodeStructure> ExtendedTypeReader::ReadInstructionArray(FILE *FilePointer) {
            XArray<BytecodeStructure> Result;
            XIndexType Index = BaseTypeReader().ReadIndex(FilePointer);
            Result.resize(Index);
            for (XIndexType I = 0; I < Index; I++) {
                Result[I] = ReadInstruction(FilePointer);
            }
            return Result;
        }

        XArray<XString> ExtendedTypeReader::ReadStringArray(FILE *FilePointer) {
            XArray<XString> Result;
            XIndexType Index = BaseTypeReader().ReadIndex(FilePointer);
            Result.resize(Index);
            for (XIndexType I = 0; I < Index; I++) {
                Result[I] = BaseTypeReader().ReadString(FilePointer);
            }
            return Result;
        }

        XArray<XIndexType> ExtendedTypeReader::ReadIndexArray(FILE *FilePointer) {
            XArray<XIndexType> Result;
            XIndexType Index = BaseTypeReader().ReadIndex(FilePointer);
            Result.resize(Index);
            for (XIndexType I = 0; I < Index; I++) {
                Result[I] = BaseTypeReader().ReadIndex(FilePointer);
            }
            return Result;
        }

        EnvFunction ExtendedTypeReader::ReadFunction(FILE *FilePointer) {
            return (EnvFunction) {0, ReadInstructionArray(FilePointer)};
        }

        EnvConstantPool::EnvConstant ExtendedTypeReader::ReadConstant(FILE *FilePointer) {
            return (EnvConstantPool::EnvConstant) {
                    static_cast<EnvConstantPool::EnvConstant::ItemKind>(BaseTypeReader().ReadInteger(FilePointer)),
                    BaseTypeReader().ReadString(FilePointer)};
        }

        XArray<EnvFunction> ExtendedTypeReader::ReadFunctionArray(FILE *FilePointer) {
            XArray<EnvFunction> Result;
            XIndexType Index = BaseTypeReader().ReadIndex(FilePointer);
            Result.resize(Index);
            for (XIndexType I = 0; I < Index; I++) {
                Result[I] = ReadFunction(FilePointer);
            }
            return Result;
        }

        EnvConstantPool ExtendedTypeReader::ReadConstants(FILE *FilePointer) {
            EnvConstantPool Result;
            XIndexType Index = BaseTypeReader().ReadIndex(FilePointer);
            Result.Constants.resize(Index);

            for (XIndexType I = 0; I < Index; I++) {
                Result.Constants[I] = ReadConstant(FilePointer);
            }

            return Result;
        }

        EnvPackageStructure ExtendedTypeReader::ReadPackage(FILE *FilePointer) {
            EnvPackageStructure Result;
            Result.Constants = ReadConstants(FilePointer);

            XIndexType FunctionsLength = BaseTypeReader().ReadIndex(FilePointer);
            for (XIndexType I = 0; I < FunctionsLength; I++) {
                Result.FunctionPool[BaseTypeReader().ReadIndex(FilePointer)] = ReadFunction(FilePointer);
            }

            Result.PackageInitializeCodes = ReadInstructionArray(FilePointer);

            Result.Statics.resize(BaseTypeReader().ReadIndex(FilePointer));

            return Result;
        }
    } // XScript
} // Reader