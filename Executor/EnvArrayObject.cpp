//
// Created by Jerry Chou on 2022/5/14.
//

#include "EnvArrayObject.hpp"

namespace XScript {
    EnvArrayObject::EnvArrayObject() : Length(0), Elements(nullptr) {

    }

    EnvArrayObject::EnvArrayObject(XIndexType Length) : Length(Length) {
        Elements = (XHeapIndexType *) (this + 1);
    }

    EnvArrayObject *CreateEnvArrayObject(XIndexType Length) {
        auto *Object = (EnvArrayObject *) malloc(sizeof(EnvArrayObject) + sizeof(XHeapIndexType) * Length);
        *Object = (EnvArrayObject) {Length};
        return Object;
    }

    void FreeEnvArrayObject(EnvArrayObject *Object) {
        free(Object);
    }

    EnvArrayObject *AddElementToBack(EnvArrayObject *Object, XHeapIndexType ToInsert) {
        auto *NewObject = (EnvArrayObject *) malloc(
                sizeof(EnvArrayObject) + sizeof(XHeapIndexType) * Object->Length + 1);
        *NewObject = (EnvArrayObject) {Object->Length + 1};
        auto Pointer = NewObject->Elements;
        for (XIndexType Index = 0; Index < Object->Length; ++Index) {
            *Pointer = Object->Elements[Index];
            Pointer++;
        }
        *Pointer = ToInsert;
        return Object;
    }

} // XScript