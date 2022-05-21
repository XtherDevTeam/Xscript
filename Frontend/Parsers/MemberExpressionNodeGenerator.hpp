//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_MEMBEREXPRESSIONNODEGENERATOR_HPP
#define XSCRIPT2_MEMBEREXPRESSIONNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

#include "FunctionCallingExpressionNodeGenerator.hpp"

namespace XScript::Generator {

        class MemberExpressionNodeGenerator : BaseGenerator {
        public:
            explicit MemberExpressionNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // Generator

#endif //XSCRIPT2_MEMBEREXPRESSIONNODEGENERATOR_HPP
