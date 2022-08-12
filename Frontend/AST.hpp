//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_AST_HPP
#define XSCRIPT2_AST_HPP

#include "../Share/Utils.hpp"
#include "Lexer.hpp"

namespace XScript {

    class AST {
    public:
        enum class TreeType : int {
/* AST output AST kinds */
/* Primary */
            NotMatch,
            Primary,
            Identifier,
            ListLiteral,
            Arguments,
            Operator,
            TypeCastingExpression,
/* Expression */
            IndexExpression,
            FunctionCallingExpression,
            MemberExpression,
            NegativeExpression,
            IncrementExpression,
            DecrementExpression,
            MultiplicationExpression,
            AdditionExpression,
            BinaryMoveExpression,
            ComparingExpression,
            EqualExpression,
            BinaryExpression,
            LogicExpression,
/* rvalue expression */
            AssignmentExpression,
            NewExpression,
/* literals */
            ArrayLiteral,
/* Descriptors */
            TypeSpecifier,
            AccessDescriptor,
            VariableDescriptor,
            MethodDescriptor,
            Descriptors,
/* Variable definition statements */
            VariableDefinition,
            VariableDeclaration,
/* Easy to implement statements */
            ReturnStatement,
            ContinueStatement,
            BreakStatement,
            CodeBlockStatement,
/* Statements */
            IfStatement,
            IfElseStatement,
            WhileStatement,
            ForStatement,
            SwitchStatement,
/* Function definition */
            FunctionDefinition,
            MethodDefinition,
            File,
            ClassExtends,
            ClassInnerStatements,
            ClassDefinition,
            ImportStatement,
            CrossPackageAccessExpression,
            MemberDefineStatement,
            NativeClassDeclarationStatement,
            TryCatchStatement,
            ThrowStatement,
            InstanceOfExpression,
            UnnamedFunctionDefinition,
            AliasStatement,
        } Type;
        Lexer::Token Node;
        XArray<AST> Subtrees;

        AST();

        AST(TreeType Type, Lexer::Token Node, XArray<AST> Subtrees);

        /**
         * @biref Construct a leaf node.
         * @param Type AST Kind of this node
         * @param Node Subtrees of this node
         */
        AST(TreeType Type, Lexer::Token Node);

        /**
         * @biref Construct a branch node.
         * @param Type AST Kind of this node
         * @param Subtrees Subtrees of this node
         */
        AST(TreeType Type, XArray<AST> Subtrees);

        /**
         * @biref Return this node is or isn't leaf node
         * @return A boolean value
         */
        [[nodiscard]] XBoolean IsLeafNode() const;

        /**
         * @brief Return this node is or isn't a failed to match node
         * @return A boolean value
         */
        [[nodiscard]] XBoolean IsNotMatchNode() const;

        /**
         * @biref Get first non-null token
         * @return A token
         */
        Lexer::Token GetFirstNotNullToken();
    };

} // XScript

#endif //XSCRIPT2_AST_HPP
