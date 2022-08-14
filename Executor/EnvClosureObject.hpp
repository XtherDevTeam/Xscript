//
// Created by p0010 on 22-8-14.
//

#ifndef XSCRIPT2_ENVCLOSUREOBJECT_HPP
#define XSCRIPT2_ENVCLOSUREOBJECT_HPP

#include "EnvFunction.hpp"

namespace XScript {

    class EnvClosureObject {
    public:
        XArray<XHeapIndexType> OuterVars;
        EnvFunction *Func;
    };

    EnvClosureObject *NewEnvClosureObject();

    void FreeEnvClosureObject(EnvClosureObject *Object);
} // XScript

#endif //XSCRIPT2_ENVCLOSUREOBJECT_HPP
