//
// Created by Jerry Chou on 2022/5/29.
//

#include "MethodDescriptorNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        MethodDescriptorNodeGenerator::MethodDescriptorNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST MethodDescriptorNodeGenerator::Parse() {
            if (L.LastToken == (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"virtual", 0, 0} or
                L.LastToken == (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"final", 0, 0} or
                L.LastToken == (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"public", 0, 0} or
                L.LastToken == (Lexer::Token) {Lexer::TokenKind::ReservedWords, L"private", 0, 0}) {
                AST Res = {AST::TreeType::MethodDescriptor, L.LastToken};
                L.Scan();
                return Res;
            } else {
                Rollback();
                return {};
            }
        }
    } // XScript
} // Generator