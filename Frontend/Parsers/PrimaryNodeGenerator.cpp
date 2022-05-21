//
// Created by Jerry Chou on 2022/5/21.
//

#include "PrimaryNodeGenerator.hpp"

namespace XScript::Generator {
    PrimaryNodeGenerator::PrimaryNodeGenerator(Lexer &L) : BaseGenerator(L) {

    }

    AST PrimaryNodeGenerator::Parse() {
        if (L.LastToken.Kind == Lexer::TokenKind::Integer or L.LastToken.Kind == Lexer::TokenKind::Decimal or
            L.LastToken.Kind == Lexer::TokenKind::Boolean or L.LastToken.Kind == Lexer::TokenKind::String) {
            AST Result = {AST::TreeType::Primary, L.LastToken};
            L.Scan(); // prepare for next time.
            return Result;
        }
        Rollback();
        return {};
    }
} // Generator