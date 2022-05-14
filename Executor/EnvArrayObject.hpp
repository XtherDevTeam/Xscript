//
// Created by Jerry Chou on 2022/5/14.
//

#ifndef XSCRIPT2_ENVARRAYOBJECT_HPP
#define XSCRIPT2_ENVARRAYOBJECT_HPP

#include "../Share/Config.hpp"

namespace XScript {

    class EnvArrayObject {
    public:
        XIndexType Length;
        XHeapIndexType* Elements;

        EnvArrayObject();

        explicit EnvArrayObject(XIndexType Length);
    };

    EnvArrayObject* CreateEnvArrayObject(XIndexType Length);

    /**
     * Free an environment array object.
     * @param Object Object to free.
     */
    void FreeEnvArrayObject(EnvArrayObject *Object);

    /**
     * Create a new object with the original elements and the element to insert.
     * @warning
     * It WON'T FREE THE ORIGINAL OBJECT!
     */
    EnvArrayObject* AddElementToBack(EnvArrayObject* Object, XHeapIndexType ToInsert);

} // XScript

#endif //XSCRIPT2_ENVARRAYOBJECT_HPP
