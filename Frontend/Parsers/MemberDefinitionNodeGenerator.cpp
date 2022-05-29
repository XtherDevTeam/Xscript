//
// Created by Jerry Chou on 2022/5/29.
//

#include "MemberDeclarationNodeGenerator.hpp"
#include "MemberDescriptorNodeGenerator.hpp"
#include "VariableStatementNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        MemberDeclarationNodeGenerator::MemberDeclarationNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST MemberDeclarationNodeGenerator::Parse() {
            AST Descriptors = {AST::TreeType::Descriptors, (XArray<AST>) {}};
            for (AST Descriptor = MemberDescriptorNodeGenerator(L).Parse();
                 !Descriptors.IsNotMatchNode(); Descriptor = MemberDescriptorNodeGenerator(L).Parse()) {
                Descriptors.Subtrees.push_back(Descriptor);
            }

            AST VariableDefOrDecl = VariableStatementNodeGenerator(L).Parse();
            if(VariableDefOrDecl.IsNotMatchNode() or VariableDefOrDecl.Type != AST::TreeType::VariableDeclaration)
                MakeException(L"MemberDefinitionNodeGenerator: InvalidSyntax -> Expected a variable declaration");

            return {AST::TreeType::MemberDeclaration, {Descriptors, VariableDefOrDecl}};
        }
    } // XScript
} // Generator