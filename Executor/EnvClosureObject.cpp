//
// Created by p0010 on 22-8-14.
//

#include "EnvClosureObject.hpp"

namespace XScript {
    EnvClosureObject *NewEnvClosureObject() {
        return new EnvClosureObject();
    }

    void FreeEnvClosureObject(EnvClosureObject *Object) {
        delete Object;
    }
} // XScript