//
// Created by Jerry Chou on 2022/5/29.
//

#include "MethodDefinitionNodeGenerator.hpp"
#include "MethodDescriptorNodeGenerator.hpp"
#include "FunctionDefinitionNodeGenerator.hpp"

namespace XScript {
    namespace Generator {

        MethodDefinitionNodeGenerator::MethodDefinitionNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST MethodDefinitionNodeGenerator::Parse() {
            AST Descriptors = {AST::TreeType::Descriptors, (XArray<AST>) {}};
            for (AST Descriptor = MethodDescriptorNodeGenerator(L).Parse();
                 !Descriptors.IsNotMatchNode(); Descriptor = MethodDescriptorNodeGenerator(L).Parse()) {
                Descriptors.Subtrees.push_back(Descriptor);
            }
            AST FunctionDefinition = FunctionDefinitionNodeGenerator(L).Parse();
            if (FunctionDefinition.IsNotMatchNode()) {
                Rollback();
                return {};
            }

            return {AST::TreeType::MethodDefinition, {Descriptors, FunctionDefinition}};
        }
    } // XScript
} // Generator