//
// Created by chou on 22-7-17.
//

#include "../Share/dlfcn.h"
#include "NativeLibrariesManager.hpp"
#include "../Share/Utils.hpp"
#include "../Share/Exceptions/InternalException.hpp"

namespace XScript {
    void NativeLibrariesManager::LoadLibrary(const XString &FullLibraryPath) {
        XIndexType HashOfPath = Hash(FullLibraryPath);
        if (LoadedLibraries.count(HashOfPath)) {
            return;
        } else {
            LoadedLibraries[HashOfPath].Handle = dlopen(wstring2string(FullLibraryPath).c_str(), RTLD_LAZY);
            if (!LoadedLibraries[HashOfPath].Handle)
                throw InternalException(L"NativeLibrariesManager::LoadLibrary(): Cannot open dynamic library.");
            typedef NativeClassInformation (*InitializerType)();

            auto Func = (InitializerType) dlsym(LoadedLibraries[HashOfPath].Handle, "Initializer");

            LoadedLibraries[HashOfPath].Information = Func();
        }
    }

    bool NativeLibrariesManager::IsLoaded(XIndexType HashOfPath) {
        return LoadedLibraries.count(HashOfPath);
    }

    NativeClass &NativeLibrariesManager::operator[](XIndexType Idx) {
        return LoadedLibraries[Idx];
    }

    void NativeLibrariesManager::FreeLibraries() {
        for (auto &I: LoadedLibraries) {
            dlclose(I.second.Handle);
        }
        LoadedLibraries = {};
    }
} // XScript