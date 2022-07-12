//
// Created by Jerry Chou on 2022/5/21.
//

#include "BaseGenerator.hpp"

namespace XScript::Generator {
    AST BaseGenerator::Parse() {
        return {};
    }

    BaseGenerator::BaseGenerator(Lexer &L) : L(L), InitialLine(L.Line), InitialColumn(L.Column),
                                             InitialPosition(L.Position), InitialLastToken(L.LastToken) {}

    void BaseGenerator::Rollback() {
        L.Line = InitialLine;
        L.Column = InitialColumn;
        L.Position = InitialPosition;
        L.LastToken = InitialLastToken;
    }

    void BaseGenerator::MakeException(const XString &Reason) const {
        throw ParserException(InitialLine, InitialColumn, Reason);
    }
} // Generator