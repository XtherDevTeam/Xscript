//
// Created by Jerry Chou on 2022/5/29.
//

#ifndef XSCRIPT2_MEMBERDECLARATIONNODEGENERATOR_HPP
#define XSCRIPT2_MEMBERDECLARATIONNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class MemberDeclarationNodeGenerator : BaseGenerator {
        public:
            explicit MemberDeclarationNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_MEMBERDECLARATIONNODEGENERATOR_HPP
