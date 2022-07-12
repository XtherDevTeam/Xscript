//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_IDENTIFIERNODEGENERATOR_HPP
#define XSCRIPT2_IDENTIFIERNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript::Generator {

    class IdentifierNodeGenerator : BaseGenerator {
    public:
        explicit IdentifierNodeGenerator(Lexer &L);

        AST Parse() override;
    };


} // Generator

#endif //XSCRIPT2_IDENTIFIERNODEGENERATOR_HPP
