//
// Created by p0010 on 22-8-12.
//

#ifndef XSCRIPT2_ALIASSTATEMENTNODEGENERATOR_HPP
#define XSCRIPT2_ALIASSTATEMENTNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript::Generator {
    class AliasStatementNodeGenerator : BaseGenerator {
    public:
        explicit AliasStatementNodeGenerator(Lexer &L);

        AST Parse() override;
    };
} // Generator

#endif //XSCRIPT2_ALIASSTATEMENTNODEGENERATOR_HPP
