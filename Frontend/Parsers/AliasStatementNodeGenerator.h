//
// Created by p0010 on 22-8-12.
//

#ifndef XSCRIPT2_ALIASSTATEMENTNODEGENERATOR_H
#define XSCRIPT2_ALIASSTATEMENTNODEGENERATOR_H

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class AliasStatementNodeGenerator : BaseGenerator {
        public:
            explicit AliasStatementNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_ALIASSTATEMENTNODEGENERATOR_H
