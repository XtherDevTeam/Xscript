//
// Created by Jerry Chou on 2022/6/18.
//

#ifndef XSCRIPT2_IMPORTSTATEMENTNODEGENERATOR_HPP
#define XSCRIPT2_IMPORTSTATEMENTNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class ImportStatementNodeGenerator : BaseGenerator {
        public:
            explicit ImportStatementNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_IMPORTSTATEMENTNODEGENERATOR_HPP
