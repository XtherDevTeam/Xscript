//
// Created by Jerry Chou on 22-7-10.
//

#ifndef XSCRIPT2_EXECUTOR_HPP
#define XSCRIPT2_EXECUTOR_HPP

#include "Environment.hpp"
#include "BytecodeInterpreter.hpp"
#include "GarbageCollection.hpp"
#include "BytecodeInterpreterPool.hpp"

namespace XScript {

    class Executor {
    public:
        Environment VM;
        GarbageCollection GC;
        BytecodeInterpreterPool Interpreters;

        Executor();

        void Load(const XString &ExecutableFilePath);

        void Init();

        void Start();

        XIndexType StartWithRuntimeDuration();

        ~Executor();
    };

} // XScript

#endif //XSCRIPT2_EXECUTOR_HPP
