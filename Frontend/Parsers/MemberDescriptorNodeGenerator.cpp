//
// Created by Jerry Chou on 2022/5/29.
//

#include "MemberDescriptorNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        MemberDescriptorNodeGenerator::MemberDescriptorNodeGenerator(Lexer &l) : BaseGenerator(l) {

        }

        AST MemberDescriptorNodeGenerator::Parse() {
            if (L.LastToken == (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"public", 0, 0} or
                L.LastToken == (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"private", 0, 0}) {
                AST Res = {AST::TreeType::MemberDescriptor, L.LastToken};
                L.Scan();
                return Res;
            } else {
                Rollback();
                return {};
            }
        }
    } // XScript
} // Generator