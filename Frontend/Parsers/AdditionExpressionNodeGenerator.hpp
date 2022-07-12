//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_ADDITIONEXPRESSIONNODEGENERATOR_HPP
#define XSCRIPT2_ADDITIONEXPRESSIONNODEGENERATOR_HPP

#include "BaseGenerator.hpp"
#include "MultiplicationExpressionNodeGenerator.hpp"

namespace XScript::Generator {

    class AdditionExpressionNodeGenerator : BaseGenerator {
    public:
        explicit AdditionExpressionNodeGenerator(Lexer &L);

        AST Parse() override;
    };


} // Generator

#endif //XSCRIPT2_ADDITIONEXPRESSIONNODEGENERATOR_HPP
