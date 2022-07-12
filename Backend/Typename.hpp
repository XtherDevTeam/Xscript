//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_TYPENAME_HPP
#define XSCRIPT2_TYPENAME_HPP

#include "../Share/Utils.hpp"

namespace XScript {
    namespace Compiler {

        class Typename {
        public:
            enum class TypenameKind : XInteger {
                Integer,
                Decimal,
                Boolean,
                Class,
                Function,
                String,
                List,
                Unknown
            } Kind;

            XIndexType ClassIndex{};

            Typename(Typename::TypenameKind kind, XIndexType classIndex);

            explicit Typename(TypenameKind kind);

        };

    } // XScript
} // Compiler

#endif //XSCRIPT2_TYPENAME_HPP
