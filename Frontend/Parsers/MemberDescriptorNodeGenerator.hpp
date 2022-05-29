//
// Created by Jerry Chou on 2022/5/29.
//

#ifndef XSCRIPT2_MEMBERDESCRIPTORNODEGENERATOR_HPP
#define XSCRIPT2_MEMBERDESCRIPTORNODEGENERATOR_HPP

#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {

        class MemberDescriptorNodeGenerator : BaseGenerator {
        public:
            explicit MemberDescriptorNodeGenerator(Lexer &L);

            AST Parse() override;
        };

    } // XScript
} // Generator

#endif //XSCRIPT2_MEMBERDESCRIPTORNODEGENERATOR_HPP
