//
// Created by Jerry Chou on 22-7-17.
//

#ifndef XSCRIPT2_NATIVELIBRARIESMANAGER_HPP
#define XSCRIPT2_NATIVELIBRARIESMANAGER_HPP

#include "../Share/Config.hpp"
#include "NativeLibrary.hpp"

namespace XScript {

    class NativeLibrariesManager {
    public:
        XMap<XIndexType, NativeLib> LoadedLibraries;

        void LoadLib(const XString &FullLibraryPath, XIndexType Alias);

        void FreeLibraries();

        bool IsLoaded(XIndexType Alias);

        NativeLib &operator[](XIndexType Alias);
    };

} // XScript

#endif //XSCRIPT2_NATIVELIBRARIESMANAGER_HPP
