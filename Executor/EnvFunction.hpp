//
// Created by Jerry Chou on 2022/6/4.
//

#ifndef XSCRIPT2_ENVFUNCTION_HPP
#define XSCRIPT2_ENVFUNCTION_HPP

#include "../Share/Config.hpp"
#include "BytecodeStructure.hpp"

namespace XScript {

    class EnvFunction {
    public:
        XIndexType PackageID;

        XArray<BytecodeStructure> BytecodeArray;

        EnvFunction();

        EnvFunction(XIndexType PackageID, XArray <BytecodeStructure> BytecodeArray);
    };

} // XScript

#endif //XSCRIPT2_ENVFUNCTION_HPP
