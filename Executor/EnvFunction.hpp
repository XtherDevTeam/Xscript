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
        XIndexType ParamsCount;
        XArray<BytecodeStructure> BytecodeArray;

        EnvFunction(XIndexType PackageID, XIndexType ParamsCount, XArray <BytecodeStructure> BytecodeArray);
    };

} // XScript

#endif //XSCRIPT2_ENVFUNCTION_HPP
