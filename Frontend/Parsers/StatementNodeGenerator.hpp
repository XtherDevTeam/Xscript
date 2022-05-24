//
// Created by Jerry Chou on 2022/5/24.
//

#ifndef XSCRIPT2_STATEMENTNODEGENERATOR_HPP
#define XSCRIPT2_STATEMENTNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class StatementNodeGenerator : BaseGenerator {
        public:
            explicit StatementNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_STATEMENTNODEGENERATOR_HPP
