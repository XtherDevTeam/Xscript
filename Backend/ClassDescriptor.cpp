//
// Created by Jerry Chou on 22-7-15.
//

#include "ClassDescriptor.hpp"

namespace XScript {
    ClassDescriptor::ClassDescriptor(XIndexType PkgID, XIndexType CID) : PackageID(PkgID), ClassID(CID) {

    }

    bool ClassDescriptor::operator==(const ClassDescriptor &rhs) const {
        return PackageID == rhs.PackageID and ClassID == rhs.ClassID;
    }

    bool ClassDescriptor::operator!=(const ClassDescriptor &rhs) const {
        return PackageID != rhs.PackageID and ClassID != rhs.ClassID;
    }
} // XScript