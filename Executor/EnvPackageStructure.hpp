//
// Created by Jerry Chou on 2022/6/17.
//

#ifndef XSCRIPT2_ENVPACKAGESTRUCTURE_HPP
#define XSCRIPT2_ENVPACKAGESTRUCTURE_HPP

#include "BytecodeStructure.hpp"
#include "EnvFunction.hpp"
#include "EnvironmentStackItem.hpp"
#include "../Backend/ConstantPool.hpp"
#include "EnvConstantPool.hpp"

namespace XScript {

    class EnvPackageStructure {
    public:
        EnvConstantPool Constants;
        
        XArray<BytecodeStructure> PackageInitializeCodes;

        XMap<XIndexType, EnvFunction> FunctionPool;

        XArray<EnvironmentStackItem> Statics;


        void ReadFromFile(FILE *FilePointer);

        void SetStatic(XHeapIndexType i, EnvironmentStackItem stackItem);

        const EnvironmentStackItem &GetStatic(XHeapIndexType i);
    };

} // XScript

#endif //XSCRIPT2_ENVPACKAGESTRUCTURE_HPP
