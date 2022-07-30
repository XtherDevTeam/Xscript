//
// Created by chou on 22-7-30.
//

#include "BytecodeInterpreterPool.hpp"

namespace XScript {
    BytecodeInterpreterPool::BytecodeInterpreterPool(Environment &Env, GarbageCollection &GC) : Env(Env), GC(GC){
        Interpreters = new BytecodeInterpreter[MaxThreadCount];
        for (XIndexType i = 0; i < MaxThreadCount;i++) {
            Interpreters[i].InterpreterEnvironment = &Env;
            Interpreters[i].GC = &GC;
            Interpreters[i].Pool = static_cast<void*>(this);
            Interpreters[i].IsBusy = false;
            Interpreters[i].ThreadID = i;
        }
    }

    XIndexType BytecodeInterpreterPool::Allocate() {
        for (XIndexType i = 0;i < MaxThreadCount;i++) {
            if(!Interpreters[i].IsBusy) {
                return i;
            }
        }
        return 0;
    }

    BytecodeInterpreter &BytecodeInterpreterPool::operator[](XIndexType Idx) const {
        return Interpreters[Idx];
    }

    BytecodeInterpreterPool::~BytecodeInterpreterPool() {
        delete[] Interpreters;
    }
} // XScript