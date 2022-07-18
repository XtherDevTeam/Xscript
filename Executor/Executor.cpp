//
// Created by Jerry Chou on 22-7-10.
//

#include <chrono>
#include "Executor.hpp"

namespace XScript {
    void Executor::Load(const XString &ExecutableFilePath) {
        VM.LoadFromFile(ExecutableFilePath, L"main", true);
    }

    void Executor::Init() {
        for (auto &PackageID: VM.LoadedPackageIDs) {
            VM.ProgramCounter = (ProgramCounterInformation) {VM.Packages[PackageID].PackageInitializeCodes,
                                                             PackageID};
            VM.Stack.FramesInformation.push_back(
                    {EnvironmentStackFramesInformation::FrameKind::FunctionStackFrame,
                     0,
                     0,
                     VM.ProgramCounter});
            Interpreter.MainLoop();
            VM.Stack.FramesInformation.pop_back();
        }
        /* correct the packageID of classes */
        for (auto &Package: VM.Packages) {
            for (auto &Class: Package.second.ClassTemplates) {
                if (!Class.second.Parent.PackageID)
                    Class.second.Parent.PackageID = Package.first;
            }
        }
    }

    Executor::Executor() : Interpreter(VM) {

    }

    void Executor::Start() {
        // 设置启动地址
        // 不用设置ProgramCounter的Package, 最后Init的一定是主包
        VM.Stack.FramesInformation.push_back(
                {EnvironmentStackFramesInformation::FrameKind::FunctionStackFrame,
                 0,
                 0,
                 VM.ProgramCounter});

        Interpreter.InstructionStackPushFunction(
                (BytecodeStructure::InstructionParam) {Hash(L"__XScriptRuntimeEntry__")});
        Interpreter.InstructionFuncInvoke((BytecodeStructure::InstructionParam) {(XHeapIndexType) {0}});
        VM.ProgramCounter.NowIndex++;
        Interpreter.MainLoop();
        Interpreter.InterpreterEnvironment.NativeLibraries.FreeLibraries();
    }

    XIndexType Executor::StartWithRuntimeDuration() {
        auto StartTime = std::chrono::system_clock::now();
        Start();
        auto Duration = std::chrono::system_clock::now() - StartTime;
        return std::chrono::duration_cast<std::chrono::milliseconds>(Duration).count();
    }
} // XScript