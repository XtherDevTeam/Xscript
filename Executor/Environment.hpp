//
// Created by Jerry Chou on 2022/5/13.
//

#ifndef XSCRIPT2_ENVIRONMENT_HPP
#define XSCRIPT2_ENVIRONMENT_HPP

#include "../Share/Utils.hpp"
#include "EnvironmentStack.hpp"
#include "EnvironmentHeap.hpp"
#include "EnvPackageStructure.hpp"
#include "../NativeLibrary/NativeLibrariesManager.hpp"
#include "ExceptionTableItem.hpp"
#include "EnvironmentThreadPool.hpp"

namespace XScript {

    /* XScript 2 Executor Environment */
    class Environment {
    public:
        EnvironmentThreadPool Threads;
        EnvironmentHeap Heap;

        XMap<XString, XString> OptionalData;

        NativeLibrariesManager NativeLibraries;

        XArray<XString> PathsToSearch;
        XArray<XIndexType> LoadedPackageIDs;
        XMap<XIndexType, EnvPackageStructure> Packages;

        XArray<ExceptionTableItem> RuntimeExceptionTable;

        void LoadFromFile(const XString &FilePath, const XString &PackageName, bool IsMainPackage);
    };

} // XScript

#endif //XSCRIPT2_ENVIRONMENT_HPP
