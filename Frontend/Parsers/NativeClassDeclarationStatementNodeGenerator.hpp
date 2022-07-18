//
// Created by Jerry Chou on 22-7-18.
//

#ifndef XSCRIPT2_NATIVECLASSDECLARATIONSTATEMENTNODEGENERATOR_HPP
#define XSCRIPT2_NATIVECLASSDECLARATIONSTATEMENTNODEGENERATOR_HPP


#include "BaseGenerator.hpp"

namespace XScript {
    namespace Generator {
        class NativeClassDeclarationStatementNodeGenerator : BaseGenerator {
        public:
            explicit NativeClassDeclarationStatementNodeGenerator(Lexer &L);

            AST Parse() override;
        };
    }
} // XScript

#endif //XSCRIPT2_NATIVECLASSDECLARATIONSTATEMENTNODEGENERATOR_HPP
