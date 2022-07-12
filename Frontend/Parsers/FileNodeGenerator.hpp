//
// Created by Jerry Chou on 2022/5/29.
//

#ifndef XSCRIPT2_FILENODEGENERATOR_HPP
#define XSCRIPT2_FILENODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {
        class FileNodeGenerator : BaseGenerator {
        public:
            explicit FileNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_FILENODEGENERATOR_HPP
