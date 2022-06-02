//
// Created by Jerry Chou on 2022/5/21.
//

#ifndef XSCRIPT2_ASSIGNMENTEXPRESSIONNODEGENERATOR_HPP
#define XSCRIPT2_ASSIGNMENTEXPRESSIONNODEGENERATOR_HPP


#include "BaseGenerator.hpp"
#include "MemberExpressionNodeGenerator.hpp"
#include "LogicExpressionNodeGenerator.hpp"

namespace XScript::Generator {

    class AssignmentExpressionNodeGenerator : BaseGenerator {
    public:
        explicit AssignmentExpressionNodeGenerator(Lexer &L);

        AST Parse() override;
    };


} // Generator

#endif //XSCRIPT2_ASSIGNMENTEXPRESSIONNODEGENERATOR_HPP
