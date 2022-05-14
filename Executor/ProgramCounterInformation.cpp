//
// Created by Jerry Chou on 2022/5/13.
//

#include "ProgramCounterInformation.hpp"

namespace XScript {
    ProgramCounterInformation::ProgramCounterInformation(XArray<BytecodeStructure> &NewCounter) {
        Pointer = &NewCounter;
        NowIndex = 0;
    }

    ProgramCounterInformation::ProgramCounterInformation(XArray<BytecodeStructure> &NewCounter, XInteger From)
            : Pointer(&NewCounter), NowIndex(From) {

    }

    ProgramCounterInformation::ProgramCounterInformation() : Pointer(nullptr), NowIndex(0) {

    }
} // XScript