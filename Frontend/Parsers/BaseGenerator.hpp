//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_BASEGENERATOR_HPP
#define XSCRIPT2_BASEGENERATOR_HPP

#include "../../Share/Utils.hpp"
#include "../Lexer.hpp"
#include "../AST.hpp"

#include "../../Share/Exceptions/ParserException.hpp"

namespace XScript::Generator {

    class BaseGenerator {
        /**
         * For rolling-back to initial state.
         */
        XInteger InitialLine, InitialColumn, InitialPosition;
        Lexer::Token InitialLastToken;
    protected:
        Lexer &L;
    public:
        explicit BaseGenerator(Lexer &L);

        /**
         * @biref Rolling-back to initial state.
         */
        void Rollback();

        /**
         * @biref Parse and return a AST node.
         * @return a AST node
         */
        virtual AST Parse();

        void MakeException(const XString &Reason) const;
    };

} // Generator

#endif //XSCRIPT2_BASEGENERATOR_HPP
