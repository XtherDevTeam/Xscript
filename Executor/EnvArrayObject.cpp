//
// Created by Jerry Chou on 2022/5/28.
//

#include "EnvArrayObject.hpp"

namespace XScript {
    XIndexType EnvArrayObject::Length() const {
        return Elements.size();
    }

    EnvArrayObject::EnvArrayObject(XIndexType Length) {
        Elements.resize(Length);
    }

    EnvArrayObject *NewEnvArrayObject(XIndexType Size) {
        return new EnvArrayObject(Size);
    }

    void FreeEnvArrayObject(EnvArrayObject *Object) {
        delete Object;
    }
} // XScript