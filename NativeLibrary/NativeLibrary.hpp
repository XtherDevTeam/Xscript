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
        XString Author;
        XString Description;
        XMap<XIndexType, NativeMethodInformation> Methods;
    };

    struct NativeClass {
        void *Handle;
        NativeClassInformation Information;

        NativeClass();
    };
};

#endif //XSCRIPT2_NATIVELIBRARY_HPP
