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
                case AST::TreeType::ImportStatement:
                    return GenerateForImportStatement(Target);
                case AST::TreeType::NativeClassDeclarationStatement:
                    return GeneratorForNativeClassDeclaration(Target);
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
            Environment.Locals = {};
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
            ClassDescriptor Extends{0, 0};
            XArray<std::pair<XString, XString>> Methods;

            if (!Target.Subtrees[1].Subtrees.empty()) {
                const auto &I = Target.Subtrees[1].Subtrees.back();
                try {
                    // 本包調用和外包調用
                    if (I.Type == AST::TreeType::Identifier) {
                        Extends = {0, Environment.MainPackage.GetClass(I.Node.Value).first};
                    } else if (I.Type == AST::TreeType::CrossPackageAccessExpression) {
                        if (I.Subtrees[1].Node.Kind != Lexer::TokenKind::Identifier)
                            throw CompilerError(I.Subtrees[1].Node.Line, I.Subtrees[1].Node.Column,
                                                L"GenerateForClassDefinition: Expected a cross package access expression with an identifier");
                        auto Pkg = Environment.GetPackage(Hash(I.Subtrees[0].Node.Value));
                        Extends = {Pkg.first, Pkg.second.GetClass(I.Subtrees[1].Node.Value).first};
                    }
                } catch (InternalException &E) {
                    throw CompilerError(I.Node.Line, I.Node.Column,
                                        L"GenerateForClassDefinition: Class " + I.Node.Value + L" doesn't exist");
                }
            }

            for (auto &Subtree: Target.Subtrees[2].Subtrees) {
                XString MethodName = ClassName + L"$" + Subtree.Subtrees[1].Subtrees[0].Node.Value;
                Environment.MainPackage.PushFunction(MethodName, {{},
                                                                  {}});

                auto Func = ParseMethodDefinition(Subtree);
                Environment.MainPackage.PushFunction(MethodName, Func);
                Methods.push_back({Subtree.Subtrees[1].Subtrees[0].Node.Value, MethodName});
            }
            Environment.MainPackage.PushClass(ClassName, (CompilingTimeClass) {ClassName, Extends, Methods});

            return {};
        }

        CompilingTimeFunction FileCompiler::ParseMethodDefinition(AST &Target) {
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

            return (CompilingTimeFunction) {Descriptors, Arguments, FunctionBytecodeArray};
        }

        XArray<BytecodeStructure> FileCompiler::GenerateForImportStatement(AST &Target) {
            Environment.ImportFromPackage(Target.Node.Value);
            return {};
        }

        XArray<BytecodeStructure> FileCompiler::GeneratorForNativeClassDeclaration(AST &Target) {
            if (!Environment.NativeLibraries.IsLoaded(Hash(Target.Subtrees[1].Node.Value))) {
                Environment.LoadNativeClass(Target.Subtrees[1].Node.Value);
            }
            XIndexType StaticIdx = Environment.MainPackage.PushStatic(Target.Subtrees[0].Node.Value,
                                                                      (SymbolItem) {(Typename) {
                                                                              Typename::TypenameKind::Unknown}, false});

            Environment.MainPackage.PackageInitializeCodes.push_back((BytecodeStructure) {
                    BytecodeStructure::InstructionEnum::native_class_new,
                    (BytecodeStructure::InstructionParam) {Hash(Target.Subtrees[1].Node.Value)}
            });

            Environment.MainPackage.PackageInitializeCodes.push_back((BytecodeStructure) {
                    BytecodeStructure::InstructionEnum::static_store,
                    (BytecodeStructure::InstructionParam) {StaticIdx}
            });
            return {};
        }
    } // XScript
} // Compiler