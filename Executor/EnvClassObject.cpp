//
// Created by Jerry Chou on 2022/5/14.
//

#include <algorithm>
#include "EnvClassObject.hpp"
#include "../Share/Exceptions/InternalException.hpp"

namespace XScript {
    bool EnvClassObject::IsInstanceOf(ClassDescriptor Idx) const {
        return Idx == Parent || Idx == Self;
    }

    XHeapIndexType EnvClassObject::GetMember(XIndexType Name) {
        try {
            return Members.at(Name);
        } catch(...) {
            throw InternalException(L"EnvClassObject::GetMember(): " + std::to_wstring(Name) + L" doesn't exist.");
        }
    }

    EnvClassObject::EnvClassObject() : Parent(0, 0), Self(0, 0) {

    }

    EnvClassObject *NewEnvClassObject() {
        return new EnvClassObject();
    }

    void FreeEnvClassObject(EnvClassObject *Object) {
        delete Object;
    }
} // XScript