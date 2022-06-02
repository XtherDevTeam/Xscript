//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_EQUALEXPRESSIONNODEGENERATOR_HPP
#define XSCRIPT2_EQUALEXPRESSIONNODEGENERATOR_HPP

#include "BaseGenerator.hpp"
#include "ComparingExpressionNodeGenerator.hpp"

namespace XScript::Generator {

    class EqualExpressionNodeGenerator : BaseGenerator {
    public:
        explicit EqualExpressionNodeGenerator(Lexer &L);

        AST Parse() override;
    };

} // Generator

#endif //XSCRIPT2_EQUALEXPRESSIONNODEGENERATOR_HPP
