//
// Created by Jerry Chou on 2022/5/21.
//

#include "CompilingTimeFunction.hpp"

#include <utility>

namespace XScript {
    namespace Compiler {
        CompilingTimeFunction::CompilingTimeFunction(XArray<Descriptor> descriptors,
                                                     const XArray<XString> &argumentsList) : ArgumentsList(
                argumentsList), Descriptors(std::move(descriptors)) {}

        CompilingTimeFunction::CompilingTimeFunction(XArray<Descriptor> descriptors,
                                                     const XArray<XString> &argumentsList,
                                                     const XArray<BytecodeStructure> &bytecodeArray) : ArgumentsList(
                argumentsList), BytecodeArray(bytecodeArray), Descriptors(std::move(descriptors)) {}
    } // XScript
} // Compiler