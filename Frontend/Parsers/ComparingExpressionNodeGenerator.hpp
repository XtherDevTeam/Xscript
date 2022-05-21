//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_COMPARINGEXPRESSIONNODEGENERATOR_HPP
#define XSCRIPT2_COMPARINGEXPRESSIONNODEGENERATOR_HPP

#include "BaseGenerator.hpp"
#include "BinaryMoveExpressionNodeGenerator.hpp"

namespace XScript::Generator {

        class ComparingExpressionNodeGenerator : BaseGenerator {

        public:
            AST Parse() override;

            explicit ComparingExpressionNodeGenerator(Lexer &L);
        };

    } // Generator

#endif //XSCRIPT2_COMPARINGEXPRESSIONNODEGENERATOR_HPP
