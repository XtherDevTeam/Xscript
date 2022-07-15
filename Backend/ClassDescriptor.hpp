//
// Created by chou on 22-7-15.
//

#ifndef XSCRIPT2_CLASSDESCRIPTOR_HPP
#define XSCRIPT2_CLASSDESCRIPTOR_HPP

#include "../Share/Config.hpp"

namespace XScript {

    class ClassDescriptor {
    public:
        XIndexType PackageID;
        XIndexType ClassID;

        ClassDescriptor(XIndexType PkgID, XIndexType CID);

        bool operator==(const ClassDescriptor &rhs) const;

        bool operator!=(const ClassDescriptor &rhs) const;
    };

} // XScript

#endif //XSCRIPT2_CLASSDESCRIPTOR_HPP
