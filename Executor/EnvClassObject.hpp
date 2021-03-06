//
// Created by Jerry Chou on 2022/5/14.
//

#ifndef XSCRIPT2_ENVCLASSOBJECT_HPP
#define XSCRIPT2_ENVCLASSOBJECT_HPP

#include "../Share/Config.hpp"
#include "../Backend/ClassDescriptor.hpp"

namespace XScript {

    class EnvClassObject {
    public:
        ClassDescriptor Parent;

        ClassDescriptor Self;

        XMap<XIndexType, XHeapIndexType> Members;

        bool IsInstanceOf(ClassDescriptor Idx) const;

        XHeapIndexType GetMember(XIndexType Name);

        EnvClassObject();
    };

    EnvClassObject *NewEnvClassObject();

    void FreeEnvClassObject(EnvClassObject *Object);

} // XScript

#endif //XSCRIPT2_ENVCLASSOBJECT_HPP
