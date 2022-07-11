//
// Created by chou on 22-7-10.
//

#include "Executor.hpp"

namespace XScript {
    void Executor::Load(const XString &ExecutableFilePath) {
        VM.LoadFromFile(ExecutableFilePath, L"main", true);
    }

    void Executor::Init() {
        for (auto &PackageID: VM.LoadedPackageIDs) {
            VM.ProgramCounter = (ProgramCounterInformation) {VM.Packages[PackageID].PackageInitializeCodes,
                                                             PackageID};
            Interpreter.MainLoop();
        }
    }

    Executor::Executor() : Interpreter(VM) {

    }

    void Executor::Start() {
        // 设置启动地址
        // 不用设置ProgramCounter的Package, 最后Init的一定是主包
        Interpreter.InstructionFuncInvoke((BytecodeStructure::InstructionParam) {Hash(L"main")});

        Interpreter.MainLoop();
    }
} // XScript