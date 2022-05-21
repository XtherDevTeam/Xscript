//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_EXPRESSIONNODEGENERATOR_HPP
#define XSCRIPT2_EXPRESSIONNODEGENERATOR_HPP

#include "BaseGenerator.hpp"
#include "LogicExpressionNodeGenerator.hpp"
#include "AssignmentExpressionNodeGenerator.hpp"

namespace XScript::Generator {

        class ExpressionNodeGenerator : BaseGenerator {
        public:
            explicit ExpressionNodeGenerator(Lexer &L);

            AST Parse() override;
        };


    } // Generator

#endif //XSCRIPT2_EXPRESSIONNODEGENERATOR_HPP
