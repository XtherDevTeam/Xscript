//
// Created by chou on 22-7-15.
//

#ifndef XSCRIPT2_MEMBERDEFINESTATEMENTNODEGENERATOR_HPP
#define XSCRIPT2_MEMBERDEFINESTATEMENTNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class MemberDefineStatementNodeGenerator : BaseGenerator {
        public:
            explicit MemberDefineStatementNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_MEMBERDEFINESTATEMENTNODEGENERATOR_HPP
