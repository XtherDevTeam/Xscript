//
// Created by chou on 22-7-20.
//

#ifndef XSCRIPT2_TRYCATCHSTATEMENTNODEGENERATOR_HPP
#define XSCRIPT2_TRYCATCHSTATEMENTNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class TryCatchStatementNodeGenerator : BaseGenerator {
        public:
            explicit TryCatchStatementNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_TRYCATCHSTATEMENTNODEGENERATOR_HPP
