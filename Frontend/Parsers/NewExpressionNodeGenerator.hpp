//
// Created by Jerry Chou on 22-7-14.
//

#ifndef XSCRIPT2_NEWEXPRESSIONNODEGENERATOR_HPP
#define XSCRIPT2_NEWEXPRESSIONNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class NewExpressionNodeGenerator : BaseGenerator {
        public:
            explicit NewExpressionNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_NEWEXPRESSIONNODEGENERATOR_HPP
