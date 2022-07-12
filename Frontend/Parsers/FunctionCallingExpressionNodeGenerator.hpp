//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_FUNCTIONCALLINGEXPRESSIONNODEGENERATOR_HPP
#define XSCRIPT2_FUNCTIONCALLINGEXPRESSIONNODEGENERATOR_HPP

#include "BaseGenerator.hpp"
#include "IdentifierNodeGenerator.hpp"
#include "IndexExpressionNodeGenerator.hpp"
#include "ArgumentsNodeGenerator.hpp"

namespace XScript::Generator {

    class FunctionCallingExpressionNodeGenerator : BaseGenerator {
    public:
        explicit FunctionCallingExpressionNodeGenerator(Lexer &L);

        AST Parse() override;
    };


} // Generator

#endif //XSCRIPT2_FUNCTIONCALLINGEXPRESSIONNODEGENERATOR_HPP
