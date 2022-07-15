//
// Created by Jerry Chou on 2022/5/14.
//

#include <algorithm>
#include "EnvClassObject.hpp"
#include "../Share/Exceptions/InternalException.hpp"

namespace XScript {
    bool EnvClassObject::IsInstanceOf(ClassDescriptor Idx) {
        return std::find(Parents.begin(), Parents.end(), Idx) != Parents.end();
    }

    XHeapIndexType EnvClassObject::GetMember(XIndexType Name) {
        if (Members.count(Name)) {
            return Members[Name];
        } else {
            throw InternalException(L"EnvClassObject::GetMember(): " + std::to_wstring(Name) + L" doesn't exist.");
        }
    }

    EnvClassObject *NewEnvClassObject() {
        return new EnvClassObject();
    }

    void FreeEnvClassObject(EnvClassObject *Object) {
        delete Object;
        return;
    }
} // XScript