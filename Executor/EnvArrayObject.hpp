//
// Created by Jerry Chou on 2022/5/28.
//

#ifndef XSCRIPT2_ENVARRAYOBJECT_HPP
#define XSCRIPT2_ENVARRAYOBJECT_HPP

#include "../Share/Config.hpp"

namespace XScript {

    class EnvArrayObject {
    public:
        XArray<XHeapIndexType> Elements;

        [[nodiscard]] XIndexType Length() const;

        explicit EnvArrayObject(XIndexType Length);
    };

    EnvArrayObject *NewEnvArrayObject(XIndexType Size);

    void FreeEnvArrayObject(EnvArrayObject *Object);

} // XScript

#endif //XSCRIPT2_ENVARRAYOBJECT_HPP
