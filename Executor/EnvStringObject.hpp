//
// Created by Jerry Chou on 2022/5/14.
//

#ifndef XSCRIPT2_ENVSTRINGOBJECT_HPP
#define XSCRIPT2_ENVSTRINGOBJECT_HPP

#include "../Share/Config.hpp"

namespace XScript {

    /**
     * XScript 2 Environment String Object
     *
     * @biref
     * It saves the string after the structure,
     * so the string data are saved starts from sizeof(XIndexType) + sizeof(XCharacter)
     *
     * @warning
     * use `CreateEnvStringObject(XIndexType Size)` to create a string object instead of using `new` operator.
     */
    class EnvStringObject {
    public:
        XIndexType Length;
        XCharacter *Dest;

        EnvStringObject();

        explicit EnvStringObject(XIndexType Length);

        void *operator new(size_t size) = delete;
    };

    EnvStringObject *CreateEnvStringObject(XIndexType StringSize);

    void FreeEnvStringObject(EnvStringObject *Pointer);

    EnvStringObject *MergeEnvStringObject(EnvStringObject *Left, EnvStringObject *Right);

    EnvStringObject *CreateEnvStringObjectFromXString(const XString &Str);
} // XScript

#endif //XSCRIPT2_ENVSTRINGOBJECT_HPP
