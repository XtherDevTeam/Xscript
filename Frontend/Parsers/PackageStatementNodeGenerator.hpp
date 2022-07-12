//
// Created by Jerry Chou on 2022/6/18.
//

#ifndef XSCRIPT2_PACKAGESTATEMENTNODEGENERATOR_HPP
#define XSCRIPT2_PACKAGESTATEMENTNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class PackageStatementNodeGenerator : BaseGenerator {
        public:
            explicit PackageStatementNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_PACKAGESTATEMENTNODEGENERATOR_HPP
