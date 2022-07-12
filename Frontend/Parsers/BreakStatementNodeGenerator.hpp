//
// Created by Jerry Chou on 2022/5/28.
//

#ifndef XSCRIPT2_BREAKSTATEMENTNODEGENERATOR_HPP
#define XSCRIPT2_BREAKSTATEMENTNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class BreakStatementNodeGenerator : BaseGenerator {
        public:
            explicit BreakStatementNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_BREAKSTATEMENTNODEGENERATOR_HPP
