//
// Created by Jerry Chou on 2022/5/26.
//

#ifndef XSCRIPT2_IFSTATEMENTNODEGENERATOR_HPP
#define XSCRIPT2_IFSTATEMENTNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class IfStatementNodeGenerator : BaseGenerator {
        public:
            explicit IfStatementNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_IFSTATEMENTNODEGENERATOR_HPP
