//
// Created by p0010 on 22-8-14.
//

#ifndef XSCRIPT2_CLOSUREDEFINITIONNODEGENERATOR_HPP
#define XSCRIPT2_CLOSUREDEFINITIONNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class ClosureDefinitionNodeGenerator : BaseGenerator {
        public:
            explicit ClosureDefinitionNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_CLOSUREDEFINITIONNODEGENERATOR_HPP
