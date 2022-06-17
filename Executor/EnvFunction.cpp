//
// Created by Jerry Chou on 2022/6/4.
//

#include "EnvFunction.hpp"

#include <utility>

namespace XScript {
    EnvFunction::EnvFunction(XIndexType PackageID, XArray<BytecodeStructure> BytecodeArray) :
            PackageID(PackageID), BytecodeArray(std::move(BytecodeArray)) {

    }
} // XScript