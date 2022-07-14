//
// Created by Jerry Chou on 2022/5/14.
//

#ifndef XSCRIPT2_ENVCLASSOBJECT_HPP
#define XSCRIPT2_ENVCLASSOBJECT_HPP

#include "../Share/Config.hpp"

namespace XScript {

    class EnvClassObject {
    public:
        XArray<XIndexType> Parents;

        XMap<XIndexType, XHeapIndexType> Members;

        bool IsInstanceOf(XIndexType Idx);

        XHeapIndexType GetMember(XIndexType Name);
    };

    EnvClassObject *NewEnvClassObject();

    void FreeEnvClassObject(EnvClassObject *Object);

} // XScript

#endif //XSCRIPT2_ENVCLASSOBJECT_HPP
