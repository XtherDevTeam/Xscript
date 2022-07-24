//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_BINARYMOVEEXPRESSIONNODEGENERATOR_HPP
#define XSCRIPT2_BINARYMOVEEXPRESSIONNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript::Generator {

    class BinaryMoveExpressionNodeGenerator : BaseGenerator {
    public:
        explicit BinaryMoveExpressionNodeGenerator(Lexer &L);

        AST Parse() override;
    };


} // Generator

#endif //XSCRIPT2_BINARYMOVEEXPRESSIONNODEGENERATOR_HPP
