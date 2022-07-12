//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_MULTIPLICATIONEXPRESSIONNODEGENERATOR_HPP
#define XSCRIPT2_MULTIPLICATIONEXPRESSIONNODEGENERATOR_HPP

#include "BaseGenerator.hpp"
#include "IncrementExpressionNodeGenerator.hpp"
#include "DecrementExpressionNodeGenerator.hpp"

namespace XScript::Generator {

    class MultiplicationExpressionNodeGenerator : BaseGenerator {
    public:
        explicit MultiplicationExpressionNodeGenerator(Lexer &L);

        AST Parse() override;
    };


} // Generator

#endif //XSCRIPT2_MULTIPLICATIONEXPRESSIONNODEGENERATOR_HPP
