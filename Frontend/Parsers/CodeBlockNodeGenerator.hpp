//
// Created by Jerry Chou on 2022/5/26.
//

#ifndef XSCRIPT2_CODEBLOCKNODEGENERATOR_HPP
#define XSCRIPT2_CODEBLOCKNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class CodeBlockNodeGenerator : BaseGenerator {
        public:
            explicit CodeBlockNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_CODEBLOCKNODEGENERATOR_HPP
