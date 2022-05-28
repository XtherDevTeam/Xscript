//
// Created by Jerry Chou on 2022/5/28.
//

#ifndef XSCRIPT2_CONTINUESTATEMENTNODEGENERATOR_HPP
#define XSCRIPT2_CONTINUESTATEMENTNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class ContinueStatementNodeGenerator : BaseGenerator {
        public:
            explicit ContinueStatementNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_CONTINUESTATEMENTNODEGENERATOR_HPP
