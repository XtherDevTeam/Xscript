//
// Created by Jerry Chou on 2022/5/28.
//

#ifndef XSCRIPT2_LISTLITERALNODEGENERATOR_HPP
#define XSCRIPT2_LISTLITERALNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class ListLiteralNodeGenerator : BaseGenerator {
        public:
            explicit ListLiteralNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_LISTLITERALNODEGENERATOR_HPP
