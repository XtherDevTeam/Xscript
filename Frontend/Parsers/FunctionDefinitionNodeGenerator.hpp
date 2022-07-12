//
// Created by Jerry Chou on 2022/5/29.
//

#ifndef XSCRIPT2_FUNCTIONDEFINITIONNODEGENERATOR_HPP
#define XSCRIPT2_FUNCTIONDEFINITIONNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class FunctionDefinitionNodeGenerator : BaseGenerator {
        public:
            explicit FunctionDefinitionNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_FUNCTIONDEFINITIONNODEGENERATOR_HPP
