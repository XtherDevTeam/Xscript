//
// Created by Jerry Chou on 2022/5/29.
//

#ifndef XSCRIPT2_COMPILERCORE_HPP
#define XSCRIPT2_COMPILERCORE_HPP

#include "../Backend/CompilerEnvironment.hpp"

namespace XScript {
    void CompileForFile(XScript::Compiler::CompilerEnvironment &Environment, const XScript::XString &FilePath);

}

#endif //XSCRIPT2_COMPILERCORE_HPP
