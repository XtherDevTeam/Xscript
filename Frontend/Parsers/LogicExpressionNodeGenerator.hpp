//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_LOGICEXPRESSIONNODEGENERATOR_HPP
#define XSCRIPT2_LOGICEXPRESSIONNODEGENERATOR_HPP

#include "BaseGenerator.hpp"
#include "BinaryExpressionNodeGenerator.hpp"

namespace XScript::Generator {

    class LogicExpressionNodeGenerator : BaseGenerator {
    public:
        explicit LogicExpressionNodeGenerator(Lexer &L);

        AST Parse() override;
    };
} // Generator

#endif //XSCRIPT2_LOGICEXPRESSIONNODEGENERATOR_HPP
