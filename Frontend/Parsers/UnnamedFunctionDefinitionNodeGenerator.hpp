//
// Created by XIaokang00010 on 2022/7/29.
//

#ifndef XSCRIPT2_UNNAMEDFUNCTIONDEFINITIONNODEGENERATOR_HPP
#define XSCRIPT2_UNNAMEDFUNCTIONDEFINITIONNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class UnnamedFunctionDefinitionNodeGenerator : BaseGenerator {
        public:
            explicit UnnamedFunctionDefinitionNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_UNNAMEDFUNCTIONDEFINITIONNODEGENERATOR_HPP
