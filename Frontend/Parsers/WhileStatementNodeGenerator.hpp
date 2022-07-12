//
// Created by Jerry Chou on 2022/5/27.
//

#ifndef XSCRIPT2_WHILESTATEMENTNODEGENERATOR_HPP
#define XSCRIPT2_WHILESTATEMENTNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class WhileStatementNodeGenerator : BaseGenerator {
        public:
            explicit WhileStatementNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_WHILESTATEMENTNODEGENERATOR_HPP
