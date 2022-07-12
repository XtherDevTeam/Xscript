//
// Created by Jerry Chou on 2022/5/21.
//

#include "Typename.hpp"

namespace XScript {
    namespace Compiler {
        Typename::Typename(Typename::TypenameKind kind, XIndexType classIndex) : Kind(kind), ClassIndex(classIndex) {}

        Typename::Typename(Typename::TypenameKind kind) : Kind(kind) {}
    } // XScript
} // Compiler