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
            BaseTypeReader().ReadIndex(FilePointer);
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
                XString FuncName = BaseTypeReader().ReadString(FilePointer);
                Result.FunctionPool[Hash(FuncName)] = ReadFunction(FilePointer);
            }

            Result.PackageInitializeCodes = ReadInstructionArray(FilePointer);

            Result.Statics.resize(BaseTypeReader().ReadIndex(FilePointer));
            for (XIndexType X = 0; X < Result.Statics.size(); X++) {
                BaseTypeReader().ReadString(FilePointer);
                BaseTypeReader().ReadBoolean(FilePointer);
            }

            return Result;
        }

        Compiler::CompilingTimeFunction ExtendedTypeReader::ReadFunctionEx(FILE *FilePointer) {
            XArray<XString> ArgList;
            ArgList.resize(BaseTypeReader().ReadIndex(FilePointer));
            return {{}, ArgList, ReadInstructionArray(FilePointer)};
        }

        XArray<Compiler::CompilingTimeFunction> ExtendedTypeReader::ReadFunctionArrayEx(FILE *FilePointer) {
            XArray<Compiler::CompilingTimeFunction> Res;
            XIndexType ReadIndex = BaseTypeReader().ReadIndex(FilePointer);
            while (ReadIndex--) {
                Res.push_back(ReadFunctionEx(FilePointer));
            }
            return Res;
        }

        Compiler::ConstantPool::ItemStructure ExtendedTypeReader::ReadConstantEx(FILE *FilePointer) {
            BaseTypeReader().ReadInteger(FilePointer);
            return (Compiler::ConstantPool::ItemStructure) {BaseTypeReader().ReadString(FilePointer)};
        }

        Compiler::ConstantPool ExtendedTypeReader::ReadConstantsEx(FILE *FilePointer) {
            Compiler::ConstantPool Res;
            XIndexType IdxForRes = BaseTypeReader().ReadIndex(FilePointer);
            while (IdxForRes--) {
                Res.Push(ReadConstantEx(FilePointer));
            }
            return Res;
        }

        Compiler::CompilingTimePackageStructure ExtendedTypeReader::ReadPackageEx(FILE *FilePointer) {
            Compiler::CompilingTimePackageStructure Result;
            Result.Constants = ReadConstantsEx(FilePointer);

            XIndexType FunctionsLength = BaseTypeReader().ReadIndex(FilePointer);
            for (XIndexType I = 0; I < FunctionsLength; I++) {
                XString FuncName = BaseTypeReader().ReadString(FilePointer);
                Result.PushFunction(FuncName, ReadFunctionEx(FilePointer));
            }

            Result.PackageInitializeCodes = ReadInstructionArray(FilePointer);

            XIndexType StaticsLength = BaseTypeReader().ReadIndex(FilePointer);
            while (StaticsLength--) {
                Result.PushStatic(BaseTypeReader().ReadString(FilePointer), (Compiler::SymbolItem) {
                        (Compiler::Typename) {Compiler::Typename::TypenameKind::Unknown},
                        BaseTypeReader().ReadBoolean(FilePointer)});
            }

            return Result;
        }


    } // XScript
} // Reader