//
// Created by Jerry Chou on 2022/6/3.
//

#ifndef XSCRIPT2_RETURNSTATEMENTNODEGENERATOR_HPP
#define XSCRIPT2_RETURNSTATEMENTNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class ReturnStatementNodeGenerator : BaseGenerator {
        public:
            explicit ReturnStatementNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_RETURNSTATEMENTNODEGENERATOR_HPP
