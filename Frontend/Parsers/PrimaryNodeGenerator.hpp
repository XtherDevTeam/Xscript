//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_PRIMARYNODEGENERATOR_HPP
#define XSCRIPT2_PRIMARYNODEGENERATOR_HPP

#include "BaseGenerator.hpp"
#include "ExpressionNodeGenerator.hpp"


namespace XScript::Generator {

    class PrimaryNodeGenerator : BaseGenerator {
    public:
        explicit PrimaryNodeGenerator(Lexer &L);

        AST Parse() override;
    };


} // Generator

#endif //XSCRIPT2_PRIMARYNODEGENERATOR_HPP
