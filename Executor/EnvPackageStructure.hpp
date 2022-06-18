//
// Created by Jerry Chou on 2022/6/17.
//

#ifndef XSCRIPT2_ENVPACKAGESTRUCTURE_HPP
#define XSCRIPT2_ENVPACKAGESTRUCTURE_HPP

#include "BytecodeStructure.hpp"
#include "EnvFunction.hpp"
#include "EnvironmentStackItem.hpp"
#include "../Backend/ConstantPool.hpp"

namespace XScript {

    class EnvPackageStructure {
    public:
        class EnvConstant {
        public:
            enum class ItemKind : XInteger {
                StringVal
            } Kind;

            XString Value;
        };

        XArray<BytecodeStructure> PackageInitializeCodes;

        XMap<XIndexType, EnvFunction> FunctionPool;

        XArray<EnvironmentStackItem> Statics;

        XArray<EnvConstant> Constants;

        void ReadFromFile(FILE *FilePointer);
    };

} // XScript

#endif //XSCRIPT2_ENVPACKAGESTRUCTURE_HPP
