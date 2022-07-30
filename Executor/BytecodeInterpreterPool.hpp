//
// Created by chou on 22-7-30.
//

#ifndef XSCRIPT2_BYTECODEINTERPRETERPOOL_HPP
#define XSCRIPT2_BYTECODEINTERPRETERPOOL_HPP

#include "BytecodeInterpreter.hpp"

namespace XScript {
    class BytecodeInterpreterPool {
    public:
        Environment &Env;
        GarbageCollection &GC;
        BytecodeInterpreter *Interpreters;

        BytecodeInterpreterPool(Environment &Env, GarbageCollection &GC);

        XIndexType Allocate();

        BytecodeInterpreter& operator[](XIndexType Idx) const;

        ~BytecodeInterpreterPool();
    };

} // XScript

#endif //XSCRIPT2_BYTECODEINTERPRETERPOOL_HPP
