//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_COMPILINGTIMEFUNCTION_HPP
#define XSCRIPT2_COMPILINGTIMEFUNCTION_HPP

#include "Typename.hpp"
#include "../Executor/BytecodeStructure.hpp"

namespace XScript::Compiler {

        class CompilingTimeFunction {
        public:
            XArray<Typename> ArgumentsList;

            XArray<BytecodeStructure> BytecodeArray;
        };

    } // Compiler

#endif //XSCRIPT2_COMPILINGTIMEFUNCTION_HPP
