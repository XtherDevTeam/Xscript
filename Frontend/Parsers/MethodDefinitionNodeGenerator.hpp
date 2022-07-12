//
// Created by Jerry Chou on 2022/5/29.
//

#ifndef XSCRIPT2_METHODDEFINITIONNODEGENERATOR_HPP
#define XSCRIPT2_METHODDEFINITIONNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class MethodDefinitionNodeGenerator : BaseGenerator {
        public:
            explicit MethodDefinitionNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_METHODDEFINITIONNODEGENERATOR_HPP
