//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_DECREMENTEXPRESSIONNODEGENERATOR_HPP
#define XSCRIPT2_DECREMENTEXPRESSIONNODEGENERATOR_HPP

#include "BaseGenerator.hpp"
#include "NegativeExpressionNodeGenerator.hpp"

namespace XScript::Generator {

        class DecrementExpressionNodeGenerator : BaseGenerator {
        public:
            explicit DecrementExpressionNodeGenerator(Lexer &L);

            AST Parse() override;
        };


    } // Generator

#endif //XSCRIPT2_DECREMENTEXPRESSIONNODEGENERATOR_HPP
