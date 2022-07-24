//
// Created by XIaokang00010 on 2022/7/24.
//

#ifndef XSCRIPT2_INSTANCEOFEXPRESSIONNODEGENERATOR_HPP
#define XSCRIPT2_INSTANCEOFEXPRESSIONNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class InstanceOfExpressionNodeGenerator : BaseGenerator {
        public:
            explicit InstanceOfExpressionNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_INSTANCEOFEXPRESSIONNODEGENERATOR_HPP
