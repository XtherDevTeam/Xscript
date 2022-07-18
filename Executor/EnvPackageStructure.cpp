//
// Created by Jerry Chou on 2022/6/17.
//

#include "EnvPackageStructure.hpp"

namespace XScript {
    void EnvPackageStructure::ReadFromFile(FILE *FilePointer) {
        /* ConstantPool Items */
        XIndexType ConstantPoolItemCount;
        fread(&ConstantPoolItemCount, sizeof(XIndexType), 1, FilePointer);
        Constants.Constants.resize(ConstantPoolItemCount);
        for (XIndexType Index = 0; Index < ConstantPoolItemCount; Index++) {
            fread(&Constants[Index].Kind, sizeof(EnvConstantPool::EnvConstant::ItemKind), 1, FilePointer);
            XIndexType StringLength;
            fread(&StringLength, sizeof(XIndexType), 1, FilePointer);
            Constants[Index].Value.resize(StringLength);
            fread((void *) Constants[Index].Value.data(), sizeof(XCharacter) * StringLength, 1, FilePointer);
        }

        /* Functions */
        XIndexType FunctionItemCount;
        fread(&FunctionItemCount, sizeof(XIndexType), 1, FilePointer);
        for (XIndexType Index = 0; Index < FunctionItemCount; Index++) {
            XIndexType NameHash;
            fread(&NameHash, sizeof(XIndexType), 1, FilePointer);

            EnvFunction Func = EnvFunction(0, XArray<BytecodeStructure>{});
            XIndexType BytecodeLength;
            fread(&BytecodeLength, sizeof(XIndexType), 1, FilePointer);
            Func.BytecodeArray.resize(BytecodeLength);
            for (XIndexType BytecodeIndex = 0; BytecodeIndex < BytecodeLength; BytecodeIndex++) {
                fread(&Func.BytecodeArray[BytecodeIndex], sizeof(BytecodeStructure), 1, FilePointer);
            }

            FunctionPool[NameHash] = Func;
        }

        /* Initiation Code */

        XIndexType BytecodeLength;
        fread(&BytecodeLength, sizeof(XIndexType), 1, FilePointer);
        PackageInitializeCodes.resize(BytecodeLength);
        for (XIndexType BytecodeIndex = 0; BytecodeIndex < BytecodeLength; BytecodeIndex++) {
            fread(&PackageInitializeCodes[BytecodeIndex], sizeof(BytecodeStructure), 1, FilePointer);
        }
    }

    void EnvPackageStructure::SetStatic(XHeapIndexType i, EnvironmentStackItem stackItem) {
        Statics[i] = stackItem;
    }

    const EnvironmentStackItem &EnvPackageStructure::GetStatic(XHeapIndexType i) {
        return Statics[i];
    }
} // XScript