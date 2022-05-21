//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_INCREMENTEXPRESSIONNODEGENERATOR_HPP
#define XSCRIPT2_INCREMENTEXPRESSIONNODEGENERATOR_HPP

#include "BaseGenerator.hpp"
#include "NegativeExpressionNodeGenerator.hpp"


namespace XScript::Generator {

        class IncrementExpressionNodeGenerator : BaseGenerator {
        public:
            explicit IncrementExpressionNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // Generator

#endif //XSCRIPT2_INCREMENTEXPRESSIONNODEGENERATOR_HPP
