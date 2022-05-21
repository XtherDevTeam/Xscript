//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_BINARYEXPRESSIONNODEGENERATOR_HPP
#define XSCRIPT2_BINARYEXPRESSIONNODEGENERATOR_HPP

#include "BaseGenerator.hpp"
#include "EqualExpressionNodeGenerator.hpp"

namespace XScript::Generator {

        class BinaryExpressionNodeGenerator : BaseGenerator {
        public:
            explicit BinaryExpressionNodeGenerator(Lexer &L);

            AST Parse() override;
        };


    } // Generator

#endif //XSCRIPT2_BINARYEXPRESSIONNODEGENERATOR_HPP
