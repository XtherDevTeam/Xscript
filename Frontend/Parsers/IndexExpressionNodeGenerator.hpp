//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_INDEXEXPRESSIONNODEGENERATOR_HPP
#define XSCRIPT2_INDEXEXPRESSIONNODEGENERATOR_HPP

#include "BaseGenerator.hpp"
#include "ExpressionNodeGenerator.hpp"

namespace XScript::Generator {

    class IndexExpressionNodeGenerator : BaseGenerator {
    public:
        explicit IndexExpressionNodeGenerator(Lexer &L);

        AST Parse() override;
    };


} // Generator

#endif //XSCRIPT2_INDEXEXPRESSIONNODEGENERATOR_HPP
