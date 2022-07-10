//
// Created by Jerry Chou on 2022/5/13.
//

#ifndef XSCRIPT2_ENVIRONMENT_HPP
#define XSCRIPT2_ENVIRONMENT_HPP

#include "../Share/Utils.hpp"
#include "EnvironmentStack.hpp"
#include "EnvironmentHeap.hpp"
#include "EnvPackageStructure.hpp"

namespace XScript {

    /* XScript 2 Executor Environment */
    class Environment {
    public:
        EnvironmentStack Stack;
        EnvironmentHeap Heap;
        ProgramCounterInformation ProgramCounter;

        XArray<XString> PathsToSearch;
        XArray<XIndexType> LoadedPackageIDs;
        XMap<XIndexType, EnvPackageStructure> DependencyPackages;
        EnvPackageStructure MainPackage;

        void LoadFromFile(const XString &FilePath, const XString& PackageName, bool IsMainPackage);
    };

} // XScript

#endif //XSCRIPT2_ENVIRONMENT_HPP
