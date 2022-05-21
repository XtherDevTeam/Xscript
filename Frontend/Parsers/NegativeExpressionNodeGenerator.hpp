//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_NEGATIVEEXPRESSIONNODEGENERATOR_HPP
#define XSCRIPT2_NEGATIVEEXPRESSIONNODEGENERATOR_HPP

#include "BaseGenerator.hpp"
#include "PrimaryNodeGenerator.hpp"
#include "MemberExpressionNodeGenerator.hpp"


namespace XScript::Generator {

        class NegativeExpressionNodeGenerator : BaseGenerator {
        public:
            explicit NegativeExpressionNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // Generator

#endif //XSCRIPT2_NEGATIVEEXPRESSIONNODEGENERATOR_HPP
