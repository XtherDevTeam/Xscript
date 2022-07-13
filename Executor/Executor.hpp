//
// Created by chou on 22-7-10.
//

#ifndef XSCRIPT2_EXECUTOR_HPP
#define XSCRIPT2_EXECUTOR_HPP

#include "Environment.hpp"
#include "BytecodeInterpreter.hpp"

namespace XScript {

    class Executor {
    public:
        Environment VM;
        BytecodeInterpreter Interpreter;

        Executor();

        void Load(const XString &ExecutableFilePath);

        void Init();

        void Start();

        XIndexType StartWithRuntimeDuration();
    };

} // XScript

#endif //XSCRIPT2_EXECUTOR_HPP
