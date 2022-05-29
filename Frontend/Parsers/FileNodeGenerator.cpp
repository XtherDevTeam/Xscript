//
// Created by Jerry Chou on 2022/5/29.
//

#include "FileNodeGenerator.hpp"
#include "FileStatementNodeGenerator.hpp"

namespace XScript {
    namespace Generator {
        FileNodeGenerator::FileNodeGenerator(Lexer &L) : BaseGenerator(L) {

        }

        AST FileNodeGenerator::Parse() {
            AST FileResult{AST::TreeType::File, (XArray<AST>) {}};

            for (AST Temp = FileStatementNodeGenerator(L).Parse(); !Temp.IsNotMatchNode();
                 Temp = FileStatementNodeGenerator(L).Parse()) {
                FileResult.Subtrees.push_back(Temp);
                if (L.LastToken.Kind != Lexer::TokenKind::Semicolon) {
                    switch (Temp.Type) {
                        case AST::TreeType::FunctionDefinition:
                            break;
                        default:
                            MakeException(L"FileNodeGenerator: InvalidSyntax -> Expected a semicolon after statements");
                    }
                } else {
                    L.Scan();
                }
            }

            return FileResult;
        }
    } // XScript
} // Generator