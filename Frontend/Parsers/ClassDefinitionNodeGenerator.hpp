//
// Created by Jerry Chou on 2022/6/2.
//

#ifndef XSCRIPT2_CLASSDEFINITIONNODEGENERATOR_HPP
#define XSCRIPT2_CLASSDEFINITIONNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class ClassDefinitionNodeGenerator : BaseGenerator {
        public:
            explicit ClassDefinitionNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_CLASSDEFINITIONNODEGENERATOR_HPP
