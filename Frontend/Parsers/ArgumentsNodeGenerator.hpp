//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_ARGUMENTSNODEGENERATOR_HPP
#define XSCRIPT2_ARGUMENTSNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

#include "ExpressionNodeGenerator.hpp"

namespace XScript::Generator {

        class ArgumentsNodeGenerator : BaseGenerator {
        public:

            explicit ArgumentsNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // Generator

#endif //XSCRIPT2_ARGUMENTSNODEGENERATOR_HPP
