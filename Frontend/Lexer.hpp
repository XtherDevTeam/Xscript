//
// Created by Jerry Chou on 2022/5/7.
//

#ifndef XSCRIPT2_LEXER_HPP
#define XSCRIPT2_LEXER_HPP

#include <algorithm>

#include "../Share/Config.hpp"
#include "../Share/Utils.hpp"
#include "../Share/XScriptException.hpp"

namespace XScript {

    /**
      * Keywords in XScript 2
      */
    static XArray<XString> LexerReservedWords{
            L"if", L"else", L"switch", L"for", L"while", L"public", L"private", L"const", L"final", L"virtual",
            L"override", L"var"
    };

    /**
      * @biref Exceptions of Lexer in XScript 2
      */
    class LexerException : XScriptException {
        std::string message;
    public:
        LexerException();

        LexerException(XInteger Line, XInteger Column, const XString &Reason);

        [[nodiscard]] const char *what() const noexcept override;
    };

    class Lexer {
    private:
        /**
         * Source codes.
         */
        XString String;
    public:
        /**
         * Kinds of tokens.
         */
        enum class TokenKind : int {
            Identifier,
            String,
            ReservedWords,
            Integer,
            Decimal,
            Boolean,
            Plus,                       // +
            Minus,                      // -
            Asterisk,                   // *
            Slash,                      // /
            PercentSign,                // %
            BinaryXOR,                  // ^
            BinaryOr,                   // |
            BinaryAnd,                  // &
            IncrementSign,              // ++
            DecrementSign,              // --
            BinaryLeftMove,             // <<
            BinaryRightMove,            // >>
            AdditionAssignment,         // +=
            SubtractionAssignment,      // -=
            MultiplicationAssignment,   // *=
            DivisionAssignment,         // /=
            RemainderAssignment,        // %=
            MoreThan,                   // >
            LessThan,                   // <
            MoreThanOrEqual,            // >=
            LessThanOrEqual,            // <=
            Equal,                      // ==
            NotEqual,                   // !=
            LogicAnd,                   // &&
            LogicOr,                    // ||
            TypeCastingSign,            // =>
            AssignSign,                 // =
            LeftParentheses,            // (
            RightParentheses,           // )
            LeftBracket,                // [
            RightBracket,               // ]
            LeftBraces,                 // {
            RightBraces,                // }
            Semicolon,                  // ;
            Colon,                      // ,
            Dot,                        // .
            EoF,
        };

        /**
         * Token type
         */
        class Token {
        public:
            TokenKind Kind;
            XInteger Line, Column;
            XString Value;

            Token();

            Token(TokenKind Kind, XString Value, XInteger Line, XInteger Column);

            bool operator==(const Token &rhs) const;

            bool operator!=(const Token &rhs) const;
        };

        /**
         * The last token has been got
         */
        Token LastToken;

        /**
         * @biref Default constructor of Lexer
         */
        Lexer();

        /**
         * @biref Initialize a Lexer with source codes.
         * @param String Source codes
         */
        explicit Lexer(XString String);

        XInteger Line{}, Column{}, Position{};

        /**
         * @biref Get next character
         * @return Next character
         */
        XCharacter NextCharacter();

        /**
         * @biref Get next token
         * @return The next token
         */
        Token Scan();

        /**
         * @biref Reset Lexer to initial state.
         */
        void Reset();
    };

} // XScript

#endif //XSCRIPT2_LEXER_HPP
