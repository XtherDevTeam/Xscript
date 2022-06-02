cmake_minimum_required(VERSION 3.0)
project(Xscript2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Xscript2
        main.cpp
        Frontend/Lexer.cpp
        Frontend/Lexer.hpp
        Share/XScriptException.cpp
        Share/XScriptException.hpp
        Share/Config.cpp
        Share/Config.hpp
        Share/Utils.cpp
        Share/Utils.hpp
        Executor/BytecodeStructure.cpp
        Executor/BytecodeStructure.hpp
        Executor/EnvironmentStackItem.cpp
        Executor/EnvironmentStackItem.hpp
        Executor/Environment.cpp
        Executor/Environment.hpp
        Executor/EnvironmentStack.cpp
        Executor/EnvironmentStack.hpp
        Executor/EnvironmentStackFramesInfomation.cpp
        Executor/EnvironmentStackFramesInfomation.hpp
        Executor/ProgramCounterInformation.cpp
        Executor/ProgramCounterInformation.hpp
        Executor/EnvironmentHeap.cpp
        Executor/EnvironmentHeap.hpp
        Executor/EnvClassObject.cpp
        Executor/EnvClassObject.hpp
        Executor/EnvStringObject.cpp
        Executor/EnvStringObject.hpp
        Executor/EnvObject.cpp
        Executor/EnvObject.hpp
        Executor/EnvArrayObject.cpp
        Executor/EnvArrayObject.hpp
        Share/Exceptions/HeapOverflowException.cpp
        Share/Exceptions/HeapOverflowException.hpp
        Executor/BytecodeInterpreter.cpp
        Executor/BytecodeInterpreter.hpp
        Share/Exceptions/BytecodeInterpretError.cpp
        Share/Exceptions/BytecodeInterpretError.hpp
        Tests/BasicTestFramework.cpp
        Tests/BasicTestFramework.hpp
        Tests/BasicTests.cpp
        Tests/BasicTests.hpp
        Frontend/AST.cpp
        Frontend/AST.hpp
        Frontend/Parsers/BaseGenerator.cpp
        Frontend/Parsers/BaseGenerator.hpp
        Share/Exceptions/ParserException.cpp
        Share/Exceptions/ParserException.hpp
        Frontend/Parsers/PrimaryNodeGenerator.cpp
        Frontend/Parsers/PrimaryNodeGenerator.hpp
        Frontend/Parsers/ExpressionNodeGenerator.cpp
        Frontend/Parsers/ExpressionNodeGenerator.hpp
        Frontend/Parsers/LogicExpressionNodeGenerator.cpp
        Frontend/Parsers/LogicExpressionNodeGenerator.hpp
        Frontend/Parsers/BinaryExpressionNodeGenerator.cpp
        Frontend/Parsers/BinaryExpressionNodeGenerator.hpp
        Frontend/Parsers/EqualExpressionNodeGenerator.cpp
        Frontend/Parsers/EqualExpressionNodeGenerator.hpp
        Frontend/Parsers/ComparingExpressionNodeGenerator.cpp
        Frontend/Parsers/ComparingExpressionNodeGenerator.hpp
        Frontend/Parsers/BinaryMoveExpressionNodeGenerator.cpp
        Frontend/Parsers/BinaryMoveExpressionNodeGenerator.hpp
        Frontend/Parsers/AdditionExpressionNodeGenerator.cpp
        Frontend/Parsers/AdditionExpressionNodeGenerator.hpp
        Frontend/Parsers/MultiplicationExpressionNodeGenerator.cpp
        Frontend/Parsers/MultiplicationExpressionNodeGenerator.hpp
        Frontend/Parsers/IncrementExpressionNodeGenerator.cpp
        Frontend/Parsers/IncrementExpressionNodeGenerator.hpp
        Frontend/Parsers/DecrementExpressionNodeGenerator.cpp
        Frontend/Parsers/DecrementExpressionNodeGenerator.hpp
        Frontend/Parsers/IndexExpressionNodeGenerator.cpp
        Frontend/Parsers/IndexExpressionNodeGenerator.hpp
        Frontend/Parsers/IdentifierNodeGenerator.cpp
        Frontend/Parsers/IdentifierNodeGenerator.hpp
        Frontend/Parsers/NegativeExpressionNodeGenerator.cpp
        Frontend/Parsers/NegativeExpressionNodeGenerator.hpp
        Frontend/Parsers/MemberExpressionNodeGenerator.cpp
        Frontend/Parsers/MemberExpressionNodeGenerator.hpp
        Frontend/Parsers/FunctionCallingExpressionNodeGenerator.cpp
        Frontend/Parsers/FunctionCallingExpressionNodeGenerator.hpp
        Frontend/Parsers/ArgumentsNodeGenerator.cpp
        Frontend/Parsers/ArgumentsNodeGenerator.hpp
        Frontend/Parsers/AssignmentExpressionNodeGenerator.cpp
        Frontend/Parsers/AssignmentExpressionNodeGenerator.hpp
        Backend/SymbolItem.cpp Backend/SymbolItem.hpp
        Backend/Typename.cpp Backend/Typename.hpp
        Backend/CompilerEnvironment.cpp Backend/CompilerEnvironment.hpp
        Backend/CompilingTimePackageStructure.cpp Backend/CompilingTimePackageStructure.hpp
        Backend/CompilingTimeFunction.cpp Backend/CompilingTimeFunction.hpp
        Backend/CompilingTimeClass.cpp Backend/CompilingTimeClass.hpp
        Share/Exceptions/InternalException.cpp Share/Exceptions/InternalException.hpp
        Backend/Compiler/ExpressionCompiler.cpp Backend/Compiler/ExpressionCompiler.hpp
        Backend/Compiler/BaseCompiler.cpp Backend/Compiler/BaseCompiler.hpp
        Share/Exceptions/CompilerError.cpp Share/Exceptions/CompilerError.hpp
        Frontend/Parsers/VariableStatementNodeGenerator.cpp Frontend/Parsers/VariableStatementNodeGenerator.hpp
        Frontend/Parsers/StatementNodeGenerator.cpp Frontend/Parsers/StatementNodeGenerator.hpp
        Backend/Compiler/StatementCompiler.cpp Backend/Compiler/StatementCompiler.hpp
        Frontend/Parsers/IfStatementNodeGenerator.cpp Frontend/Parsers/IfStatementNodeGenerator.hpp
        Frontend/Parsers/CodeBlockNodeGenerator.cpp Frontend/Parsers/CodeBlockNodeGenerator.hpp
        Frontend/Parsers/WhileStatementNodeGenerator.cpp Frontend/Parsers/WhileStatementNodeGenerator.hpp
        Frontend/Parsers/ForStatementNodeGenerator.cpp Frontend/Parsers/ForStatementNodeGenerator.hpp
        Frontend/Parsers/ListLiteralNodeGenerator.cpp Frontend/Parsers/ListLiteralNodeGenerator.hpp
        Executor/EnvArrayObject.cpp Executor/EnvArrayObject.hpp
        Frontend/Parsers/BreakStatementNodeGenerator.cpp Frontend/Parsers/BreakStatementNodeGenerator.hpp
        Frontend/Parsers/ContinueStatementNodeGenerator.cpp Frontend/Parsers/ContinueStatementNodeGenerator.hpp
        Frontend/Parsers/FunctionDefinitionNodeGenerator.cpp
        Frontend/Parsers/FunctionDefinitionNodeGenerator.hpp Frontend/Parsers/FunctionDefinitionNodeGenerator.hpp
        Frontend/Parsers/MethodDescriptorNodeGenerator.cpp Frontend/Parsers/MethodDescriptorNodeGenerator.hpp
        Frontend/Parsers/MethodDefinitionNodeGenerator.cpp Frontend/Parsers/MethodDefinitionNodeGenerator.hpp
        Frontend/Parsers/FileStatementNodeGenerator.cpp
        Frontend/Parsers/FileStatementNodeGenerator.hpp Frontend/Parsers/FileNodeGenerator.cpp
        Frontend/Parsers/FileNodeGenerator.hpp Backend/Compiler/FileCompiler.cpp Backend/Compiler/FileCompiler.hpp
        Core/CompilerCore.cpp Core/CompilerCore.hpp
        Core/Serializatior/BaseTypeSerializatior.cpp Core/Serializatior/BaseTypeSerializatior.hpp
        Core/Serializatior/ExtendedTypeSerializatior.cpp Core/Serializatior/ExtendedTypeSerializatior.hpp
        Frontend/Parsers/ClassDefinitionNodeGenerator.cpp Frontend/Parsers/ClassDefinitionNodeGenerator.hpp
        )
