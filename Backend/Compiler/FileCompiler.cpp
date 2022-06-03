//
// Created by Jerry Chou on 2022/5/29.
//

#include "FileCompiler.hpp"
#include "StatementCompiler.hpp"
#include "ExpressionCompiler.hpp"
#include "../../Share/Exceptions/InternalException.hpp"
#include "../../Share/Exceptions/CompilerError.hpp"

namespace XScript {
    namespace Compiler {
        FileCompiler::FileCompiler(CompilerEnvironment &Environment) : BaseCompiler(Environment) {

        }

        XArray<BytecodeStructure> FileCompiler::Generate(AST &Target) {
            switch (Target.Type) {
                case AST::TreeType::FunctionDefinition:
                    return GenerateForFunctionDefinition(Target);
                case AST::TreeType::VariableDeclaration:
                    return GenerateForVariableDeclaration(Target);
                case AST::TreeType::VariableDefinition:
                    return GenerateForVariableDefinition(Target);
                case AST::TreeType::ClassDefinition:
                    return GenerateForClassDefinition(Target);
                default:
                    throw InternalException(L"FileCompiler::Generate : Invalid invoke");
            }
        }

        XArray<BytecodeStructure> FileCompiler::GenerateForFunctionDefinition(AST &Target) {
            XArray<XString> Params;

            XArray<BytecodeStructure> Structure;

            /**
             * initialize params
             */
            for (auto &I: Target.Subtrees[1].Subtrees) {
                Params.push_back(I.Node.Value);
            }

            CompilingTimeFunction Func{
                    XArray<CompilingTimeFunction::Descriptor>{CompilingTimeFunction::Descriptor::Public}, Params,
                    {}};

            auto FuncIndex = Environment.MainPackage.PushFunction(Target.Subtrees[0].Node.Value, Func);

            /**
             * Push function pointer to statics
             */
            auto Idx = Environment.MainPackage.PushStatic(Target.Subtrees[0].Node.Value,
                                                          (SymbolItem) {(Typename) {Typename::TypenameKind::Unknown},
                                                                        true});

            Environment.MainPackage.PackageInitializeCodes.push_back((BytecodeStructure) {
                    BytecodeStructure::InstructionEnum::stack_push_function,
                    (BytecodeStructure::InstructionParam) {Hash(Target.Subtrees[0].Node.Value)}
            });

            Environment.MainPackage.PackageInitializeCodes.push_back((BytecodeStructure) {
                    BytecodeStructure::InstructionEnum::static_store,
                    (BytecodeStructure::InstructionParam) {Idx}
            });

            /**
             * generate bytecodes
             */
            auto Backup = Environment.Locals;
            for (auto &I: Target.Subtrees[1].Subtrees) {
                Environment.PushLocal(I.Node.Value, {(Typename) {Typename::TypenameKind::Unknown}, {}});
            }

            Structure = StatementCompiler(Environment).GenerateForCodeBlock(Target.Subtrees[2]);

            Environment.Locals = Backup;

            Environment.MainPackage.Functions[FuncIndex].second.BytecodeArray = Structure;
            return {};
        }

        XArray<BytecodeStructure> FileCompiler::GenerateForVariableDeclaration(AST &Target) {
            Environment.MainPackage.PushStatic(Target.Subtrees[0].Node.Value,
                                               (SymbolItem) {(Typename) {Typename::TypenameKind::Unknown}, false});
            return {};
        }

        XArray<BytecodeStructure> FileCompiler::GenerateForVariableDefinition(AST &Target) {
            auto Index = Environment.MainPackage.PushStatic(Target.Subtrees[0].Node.Value,
                                                            (SymbolItem) {(Typename) {Typename::TypenameKind::Unknown},
                                                                          false});

            MergeArray(Environment.MainPackage.PackageInitializeCodes,
                       ExpressionCompiler(Environment).Generate(Target.Subtrees[1]));
            Environment.MainPackage.PackageInitializeCodes.push_back(
                    (BytecodeStructure) {BytecodeStructure::InstructionEnum::static_store,
                                         (BytecodeStructure::InstructionParam) {Index}}
            );
            return {};
        }

        XArray<BytecodeStructure> FileCompiler::GenerateForFile(AST &Target) {
            XArray<BytecodeStructure> Result;
            for (auto &Subtree: Target.Subtrees) {
                MergeArray(Result, Generate(Subtree));
            }
            return Result;
        }

        XArray<BytecodeStructure> FileCompiler::GenerateForClassDefinition(AST &Target) {
            XString ClassName = Target.Subtrees[0].Node.Value;
            XArray<XIndexType> Extends;
            XArray<XString> Methods;

            for (auto &I: Target.Subtrees[1].Subtrees) {
                try {
                    Extends.push_back(Environment.MainPackage.GetClass(I.Node.Value).first);
                } catch (InternalException &E) {
                    throw CompilerError(I.Node.Line, I.Node.Column,
                                        L"GenerateForClassDefinition: Class " + I.Node.Value + L" doesn't exist");
                }
            }
            for (auto &Subtree: Target.Subtrees[2].Subtrees) {
                auto Func = ParseMethodDefinition(Subtree);
                Environment.MainPackage.PushFunction(ClassName + L"$" + Func.first, Func.second);
                Methods.push_back(ClassName + L"$" + Func.first);
            }
            Environment.MainPackage.PushClass(ClassName, (CompilingTimeClass) {Extends, Methods});

            return {};
        }

        std::pair<XString, CompilingTimeFunction> FileCompiler::ParseMethodDefinition(AST &Target) {
            XArray<CompilingTimeFunction::Descriptor> Descriptors;
            XArray<XString> Arguments;
            XArray<BytecodeStructure> FunctionBytecodeArray;
            for (auto &I: Target.Subtrees[0].Subtrees) {
                if (I.Node.Value == L"public") {
                    Descriptors.push_back(CompilingTimeFunction::Descriptor::Public);
                } else if (I.Node.Value == L"private") {
                    Descriptors.push_back(CompilingTimeFunction::Descriptor::Private);
                } else {
                    throw CompilerError(I.Node.Line, I.Node.Column,
                                        L"GenerateForClassDefinition: Invalid method descriptor");
                }
            }

            XString MethodName = Target.Subtrees[1].Subtrees[0].Node.Value;

            for (auto &I: Target.Subtrees[1].Subtrees[1].Subtrees) {
                Arguments.push_back(I.Node.Value);
            }

            auto Backup = Environment.Locals;
            Arguments.push_back(L"this");
            Environment.Locals = {};
            for (auto &I: Arguments) {
                Environment.PushLocal(I, {(Typename) {Typename::TypenameKind::Unknown}, false});
            }

            FunctionBytecodeArray = StatementCompiler(Environment).GenerateForCodeBlock(Target.Subtrees[1].Subtrees[2]);

            Environment.Locals = Backup;

            return {MethodName, (CompilingTimeFunction) {Descriptors, Arguments, FunctionBytecodeArray}};
        }
    } // XScript
} // Compiler