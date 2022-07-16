//
// Created by chou on 22-7-15.
//

#ifndef XSCRIPT2_ENVCLASSTEMPLATE_HPP
#define XSCRIPT2_ENVCLASSTEMPLATE_HPP

#include "../Share/Config.hpp"
#include "../Backend/ClassDescriptor.hpp"

namespace XScript {

    class EnvClassTemplate {
    public:
        ClassDescriptor Parent;

        /* <AliasName, RealName> */
        XMap<XIndexType, XIndexType> Methods;

        EnvClassTemplate();
    };

} // XScript

#endif //XSCRIPT2_ENVCLASSTEMPLATE_HPP
