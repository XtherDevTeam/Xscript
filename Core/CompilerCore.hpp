//
// Created by Jerry Chou on 2022/5/29.
//

#ifndef XSCRIPT2_COMPILERCORE_HPP
#define XSCRIPT2_COMPILERCORE_HPP

#include "../Backend/CompilerEnvironment.hpp"

namespace XScript {
    void CompileForFile(Compiler::CompilerEnvironment &Environment, const XString &FilePath);

    XString GetFilenameFromPath(const XString& Filepath);

    void GenerateRuntimeFunction(Compiler::CompilerEnvironment &Environment);

    void OutputBinary(Compiler::CompilerEnvironment &Environment, const XString &FilePath);
}

#endif //XSCRIPT2_COMPILERCORE_HPP
