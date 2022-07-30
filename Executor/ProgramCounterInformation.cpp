//
// Created by Jerry Chou on 2022/5/13.
//

#include "ProgramCounterInformation.hpp"

namespace XScript {
    ProgramCounterInformation::ProgramCounterInformation(XArray<BytecodeStructure> &NewCounter, XIndexType InWhichPackage) {
        Pointer = &NewCounter;
        NowIndex = 0;
        Package = InWhichPackage;
    }

    ProgramCounterInformation::ProgramCounterInformation(XArray<BytecodeStructure> &NewCounter, XInteger From)
            : Pointer(&NewCounter), NowIndex(From), Package(0) {

    }

    ProgramCounterInformation::ProgramCounterInformation() : Pointer(nullptr), NowIndex(0), Package(0) {

    }
} // XScript