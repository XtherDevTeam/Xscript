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
            VM.Threads[0].PC = (ProgramCounterInformation) {VM.Packages[PackageID].PackageInitializeCodes,
                                                             PackageID};
            VM.Threads[0].Stack.FramesInformation.push_back(
                    {EnvironmentStackFramesInformation::FrameKind::FunctionStackFrame,
                     0,
                     0,
                     VM.Threads[0].PC});
            Interpreters[0].MainLoop();
        }
        /* correct the packageID of classes */
        for (auto &Package: VM.Packages) {
            for (auto &Class: Package.second.ClassTemplates) {
                if (!Class.second.Parent.PackageID)
                    Class.second.Parent.PackageID = Package.first;
            }
        }
    }

    Executor::Executor() : Interpreters(VM, GC), GC(VM) {
    }

    void Executor::Start() {
        // 设置启动地址
        // 不用设置ProgramCounter的Package, 最后Init的一定是主包
        VM.Threads[0].Stack.FramesInformation.push_back(
                {EnvironmentStackFramesInformation::FrameKind::FunctionStackFrame,
                 0,
                 0,
                 VM.Threads[0].PC});

        VM.Threads[0].PC = (ProgramCounterInformation) {VM.Packages[VM.LoadedPackageIDs.back()].PackageInitializeCodes,
                                                        VM.LoadedPackageIDs.back()};
        Interpreters[0].InstructionStackPushFunction(
                (BytecodeStructure::InstructionParam) {builtin_hash_code___XScriptRuntimeEntry__});
        Interpreters[0].InstructionFuncInvoke((BytecodeStructure::InstructionParam) {(XHeapIndexType) {0}});
        VM.Threads[0].PC.NowIndex++;
        Interpreters[0].MainLoop();
        Interpreters[0].InterpreterEnvironment->NativeLibraries.FreeLibraries();
    }

    XIndexType Executor::StartWithRuntimeDuration() {
        auto StartTime = std::chrono::system_clock::now();
        Start();
        auto Duration = std::chrono::system_clock::now() - StartTime;
        return std::chrono::duration_cast<std::chrono::milliseconds>(Duration).count();
    }
} // XScript