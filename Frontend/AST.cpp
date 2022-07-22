//
// Created by Jerry Chou on 2022/5/21.
//

#include "AST.hpp"

namespace XScript {
    AST::AST() : Type(TreeType::NotMatch) {}

    AST::AST(AST::TreeType Type, Lexer::Token Node, XArray<AST> Subtrees) : Type(Type), Node(std::move(Node)),
                                                                            Subtrees(std::move(Subtrees)) {}

    AST::AST(AST::TreeType Type, Lexer::Token Node) : Type(Type), Subtrees(), Node(std::move(Node)) {}

    AST::AST(AST::TreeType Type, XArray<AST> Subtrees) : Type(Type), Node(), Subtrees(std::move(Subtrees)) {}

    XBoolean AST::IsLeafNode() const {
        return Subtrees.empty();
    }

    XBoolean AST::IsNotMatchNode() const {
        return Type == TreeType::NotMatch;
    }

    Lexer::Token AST::GetFirstNotNullToken() {
        if (IsNotMatchNode()) {
            return {};
        } else if (IsLeafNode()) {
            return Node;
        } else {
            for (auto &i: Subtrees) {
                Lexer::Token R = i.GetFirstNotNullToken();
                if (R.Kind != Lexer::TokenKind::EoF)
                    return R;
            }
            return {};
        }
    }
} // XScript