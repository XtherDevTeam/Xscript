//
// Created by chou on 22-7-10.
//

#include "Executor.hpp"

namespace XScript {
    void Executor::Load(const XString& ExecutableFilePath) {
        VM.LoadFromFile(ExecutableFilePath, L"main", true);
    }

    void Executor::Init() {
        for (auto &PackageID : VM.LoadedPackageIDs) {
            VM.ProgramCounter = (ProgramCounterInformation){VM.DependencyPackages[PackageID].PackageInitializeCodes};
            Interpreter.MainLoop();
        }
    }

    Executor::Executor() : Interpreter(VM) {

    }

    void Executor::Start() {
        /* TODO: add invoke command */
    }
} // XScript