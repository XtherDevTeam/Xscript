//
// Created by Jerry Chou on 2022/6/4.
//

#include "EnvFunction.hpp"

#include <utility>

namespace XScript {
    EnvFunction::EnvFunction(XIndexType PackageID, XIndexType ParamsCount, XArray<BytecodeStructure> BytecodeArray) :
            PackageID(PackageID), ParamsCount(ParamsCount), BytecodeArray(std::move(BytecodeArray)) {

    }
} // XScript