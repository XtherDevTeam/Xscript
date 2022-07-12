//
// Created by Jerry Chou on 2022/5/28.
//

#ifndef XSCRIPT2_FORSTATEMENTNODEGENERATOR_HPP
#define XSCRIPT2_FORSTATEMENTNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class ForStatementNodeGenerator : BaseGenerator {
        public:
            explicit ForStatementNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_FORSTATEMENTNODEGENERATOR_HPP
