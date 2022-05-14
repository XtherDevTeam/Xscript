//
// Created by Jerry Chou on 2022/5/14.
//

#include "EnvStringObject.hpp"

namespace XScript {
    EnvStringObject::EnvStringObject() : Length(0), Dest(nullptr) {

    }

    EnvStringObject::EnvStringObject(XIndexType Length) : Length(Length),
                                                          Dest((XCharacter *) (this + 1)) {

    }

    EnvStringObject *CreateEnvStringObject(XIndexType StringSize) {
        auto *Object = (EnvStringObject *) malloc(sizeof(EnvStringObject) + sizeof(XCharacter) * StringSize);
        (*Object) = EnvStringObject{StringSize};
        return Object;
    }

    void FreeEnvStringObject(EnvStringObject *Pointer) {
        Pointer->~EnvStringObject();
        free(Pointer);
    }

    EnvStringObject *MergeEnvStringObject(EnvStringObject *Left, EnvStringObject *Right) {
        auto Object = CreateEnvStringObject(Left->Length + Right->Length);
        auto Pointer = Object->Dest;
        for (XIndexType Index = 0; Index < Left->Length; ++Index) {
            *Pointer = Left->Dest[Index];
            Pointer++;
        }
        for (XIndexType Index = 0; Index < Right->Length; ++Index) {
            *Pointer = Left->Dest[Index];
            Pointer++;
        }
        *Pointer = L'\0';
        return Object;
    }

    EnvStringObject *CreateEnvStringObjectFromXString(const XString& Str) {
        auto Object = CreateEnvStringObject(Str.length());
        auto Pointer = Object->Dest;
        for (XCharacter Index : Str) {
            *Pointer = Index;
            Pointer++;
        }
        *Pointer = L'\0';
        return Object;
    }
} // XScript