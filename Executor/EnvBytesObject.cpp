//
// Created by chou on 22-7-31.
//

#include "EnvBytesObject.hpp"

namespace XScript {
    EnvBytesObject::EnvBytesObject() : Length(0), Dest(0) {

    }

    EnvBytesObject::EnvBytesObject(XIndexType Length) : Length(Length),
                                                        Dest(0)  {

    }

    EnvBytesObject *CreateEnvBytesObject(XIndexType StringSize) {
        auto *Object = (EnvBytesObject *) malloc(sizeof(EnvBytesObject) + sizeof(char) * StringSize);
        (*Object) = EnvBytesObject{StringSize};
        return Object;
    }

    void FreeEnvBytesObject(EnvBytesObject *Pointer) {
        Pointer->~EnvBytesObject();
        free(Pointer);
    }

    EnvBytesObject *MergeEnvBytesObject(EnvBytesObject *Left, EnvBytesObject *Right) {
        auto Object = CreateEnvBytesObject(Left->Length + Right->Length);
        auto Pointer = &Object->Dest;
        for (XIndexType Index = 0; Index < Left->Length; ++Index) {
            *Pointer = (&Left->Dest)[Index];
            Pointer++;
        }
        for (XIndexType Index = 0; Index < Right->Length; ++Index) {
            *Pointer = (&Right->Dest)[Index];
            Pointer++;
        }
        *Pointer = L'\0';
        return Object;
    }

    EnvBytesObject *CreateEnvBytesObjectFromXBytes(const XBytes &Str) {
        auto Object = CreateEnvBytesObject(Str.length() + 1);
        auto Pointer = &Object->Dest;
        for (char Index: Str) {
            *Pointer = Index;
            Pointer++;
        }
        *Pointer = '\0';
        return Object;
    }

    XBytes CovertToXBytes(EnvBytesObject *Object) {
        return {&Object->Dest};
    }
} // XScript