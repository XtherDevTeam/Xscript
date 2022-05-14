//
// Created by Jerry Chou on 2022/5/13.
//

#ifndef XSCRIPT2_PROGRAMCOUNTERINFORMATION_HPP
#define XSCRIPT2_PROGRAMCOUNTERINFORMATION_HPP

#include "../Share/Utils.hpp"
#include "BytecodeStructure.hpp"

namespace XScript {

    class ProgramCounterInformation {
    public:
        XArray<BytecodeStructure>* Pointer;
        XIndexType NowIndex;

        explicit ProgramCounterInformation(XArray<BytecodeStructure> &NewCounter);

        explicit ProgramCounterInformation(XArray<BytecodeStructure> &Counter, XInteger Start);

        ProgramCounterInformation();
    };

} // XScript

#endif //XSCRIPT2_PROGRAMCOUNTERINFORMATION_HPP
