//
// Created by chou on 22-7-31.
//

#ifndef XSCRIPT2_ENVBYTESOBJECT_HPP
#define XSCRIPT2_ENVBYTESOBJECT_HPP

#include "../Share/Utils.hpp"

namespace XScript {
    /**
     * XScript 2 Environment String Object
     *
     * @biref
     * It saves the string after the structure,
     * so the string data are saved starts from sizeof(XIndexType) + sizeof(XCharacter)
     *
     * @warning
     * use `CreateEnvBytesObject(XIndexType Size)` to create a string object instead of using `new` operator.
     */
    class EnvBytesObject {
    public:
        XIndexType Length;
        char Dest;

        EnvBytesObject();

        explicit EnvBytesObject(XIndexType Length);

        void *operator new(size_t size) = delete;
    };

    EnvBytesObject *CreateEnvBytesObject(XIndexType StringSize);

    void FreeEnvBytesObject(EnvBytesObject *Pointer);

    EnvBytesObject *MergeEnvBytesObject(EnvBytesObject *Left, EnvBytesObject *Right);

    EnvBytesObject *CreateEnvBytesObjectFromXBytes(const XBytes &Str);

    XBytes CovertToXBytes(EnvBytesObject *Object);

} // XScript

#endif //XSCRIPT2_ENVBYTESOBJECT_HPP
