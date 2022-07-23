//
// Created by XIaokang00010 on 2022/7/23.
//

#ifndef XSCRIPT2_THROWSTATEMENTNODEGENERATOR_HPP
#define XSCRIPT2_THROWSTATEMENTNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class ThrowStatementNodeGenerator : BaseGenerator {
        public:
            explicit ThrowStatementNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_THROWSTATEMENTNODEGENERATOR_HPP
