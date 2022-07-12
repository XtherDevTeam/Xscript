//
// Created by Jerry Chou on 2022/5/29.
//

#ifndef XSCRIPT2_FILESTATEMENTNODEGENERATOR_HPP
#define XSCRIPT2_FILESTATEMENTNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class FileStatementNodeGenerator : BaseGenerator {
        public:
            explicit FileStatementNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_FILESTATEMENTNODEGENERATOR_HPP
