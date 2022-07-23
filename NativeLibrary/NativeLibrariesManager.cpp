//
// Created by Jerry Chou on 22-7-17.
//

#include "../Share/dlfcn.h"
#include "NativeLibrariesManager.hpp"
#include "../Share/Utils.hpp"
#include "../Share/Exceptions/InternalException.hpp"

namespace XScript {
    void NativeLibrariesManager::LoadLib(const XString &FullLibraryPath, XIndexType Alias) {
        if (LoadedLibraries.count(Alias)) {
            return;
        } else {
            LoadedLibraries[Alias].Handle = dlopen(wstring2string(FullLibraryPath).c_str(), RTLD_LAZY);
            if (!LoadedLibraries[Alias].Handle) {
                LoadedLibraries.erase(Alias);
                throw InternalException(L"NativeLibrariesManager::LoadLib(): Cannot open dynamic library.");
            }
            typedef NativeClassInformation (*InitializerType)();

            auto Func = (InitializerType) dlsym(LoadedLibraries[Alias].Handle, "Initialize");

            LoadedLibraries[Alias].Information = Func();
        }
    }

    bool NativeLibrariesManager::IsLoaded(XIndexType Alias) {
        return LoadedLibraries.count(Alias);
    }

    NativeClass &NativeLibrariesManager::operator[](XIndexType Alias) {
        return LoadedLibraries[Alias];
    }

    void NativeLibrariesManager::FreeLibraries() {
        for (auto &I: LoadedLibraries) {
            I.second.Information.Methods.clear(); // quick fix
            dlclose(I.second.Handle);
        }
        LoadedLibraries = {};
    }
} // XScript