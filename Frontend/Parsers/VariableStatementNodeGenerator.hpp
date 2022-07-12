
//
// Created by Jerry Chou on 2022/5/24.
//

#ifndef XSCRIPT2_VARIABLESTATEMENTNODEGENERATOR_HPP
#define XSCRIPT2_VARIABLESTATEMENTNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class VariableStatementNodeGenerator : BaseGenerator {

        public:
            explicit VariableStatementNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_VARIABLESTATEMENTNODEGENERATOR_HPP
