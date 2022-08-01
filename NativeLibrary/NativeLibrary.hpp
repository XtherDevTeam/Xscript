//
// Created by Jerry Chou on 22-7-17.
//

#ifndef XSCRIPT2_NATIVELIBRARY_HPP
#define XSCRIPT2_NATIVELIBRARY_HPP

#include <functional>
#include "../Share/Config.hpp"

namespace XScript {
    struct ParamToMethod {
        void *InterpreterPointer;
        XIndexType ParamsCount;
    };

    using NativeMethodPointer = std::function<void(ParamToMethod)>;

    struct NativeMethodInformation {
        XIndexType ParamsCount;
        NativeMethodPointer Method;
    };

    struct NativeClassInformation {
        XString ClassName;
        XMap<XIndexType, NativeMethodInformation> Methods;
    };

    struct NativeLibraryInformation {
        XString Author;
        XString Description;
        XMap<XIndexType, NativeClassInformation> Classes;
    };

    struct NativeLib {
        void *Handle;
        NativeLibraryInformation Information;

        NativeLib();
    };
};

#endif //XSCRIPT2_NATIVELIBRARY_HPP
