//
// Created by Jerry Chou on 2022/5/29.
//

#ifndef XSCRIPT2_METHODDESCRIPTORNODEGENERATOR_HPP
#define XSCRIPT2_METHODDESCRIPTORNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class MethodDescriptorNodeGenerator : BaseGenerator {
        public:
            explicit MethodDescriptorNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_METHODDESCRIPTORNODEGENERATOR_HPP
