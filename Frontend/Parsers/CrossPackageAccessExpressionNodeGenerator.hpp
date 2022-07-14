//
// Created by Jerry Chou on 22-7-13.
//

#ifndef XSCRIPT2_CROSSPACKAGEACCESSEXPRESSIONNODEGENERATOR_HPP
#define XSCRIPT2_CROSSPACKAGEACCESSEXPRESSIONNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class CrossPackageAccessExpressionNodeGenerator : BaseGenerator {
        public:
            explicit CrossPackageAccessExpressionNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_CROSSPACKAGEACCESSEXPRESSIONNODEGENERATOR_HPP
