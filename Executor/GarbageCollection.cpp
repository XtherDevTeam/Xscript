//
// Created by chou on 22-7-19.
//

#include <queue>
#include <set>
#include "GarbageCollection.hpp"

#include "../Share/Xqueue.hpp"
#include "BytecodeInterpreter.hpp"
#include "BytecodeInterpreterPool.hpp"

namespace XScript {
    /**
     * BFS
     */
    void GarbageCollection::Start(bool force) {
        auto *Interpreter = static_cast<BytecodeInterpreter *>(InterpreterPointer);
        if (!Started && (force || PassiveCheck())) {
            Started = true;
            std::queue<XHeapIndexType> Queue;
            for (auto &I: Interpreter->InterpreterEnvironment->Packages) {
                for (auto &J: I.second.Statics) {
                    if (J.Kind == EnvironmentStackItem::ItemKind::HeapPointer)
                        Queue.push(J.Value.HeapPointerVal);
                }
            }
            for (XIndexType TID = 0; TID < MaxThreadCount; TID++) {
                for (auto &I: Interpreter->InterpreterEnvironment->Threads[TID].Stack.Elements) {
                    if (I.Kind == EnvironmentStackItem::ItemKind::HeapPointer)
                        Queue.push(I.Value.HeapPointerVal);
                }
            }

            XHeapIndexType AAllocCount = 0;
            while (!Queue.empty()) {
                AAllocCount++;
                auto &Element = Interpreter->InterpreterEnvironment->Heap.HeapData[Queue.front()];
                Queue.pop();
                if (Element.Marked)
                    continue;
                Element.Marked = true;
                switch (Element.Kind) {
                    case EnvObject::ObjectKind::ClassObject: {
                        for (auto &I: Element.Value.ClassObjectPointer->Members) {
                            Queue.push(I.second);
                        }
                        break;
                    }
                    case EnvObject::ObjectKind::ArrayObject:
                        for (auto &I: Element.Value.ArrayObjectPointer->Elements) {
                            Queue.push(I);
                        }
                        break;
                    case EnvObject::ObjectKind::ClosurePointer:
                        for (auto &I: Element.Value.ClosurePointer->OuterVars) {
                            Queue.push(I);
                        }
                        break;
                    default:
                        break;
                }
            }
            XHeapIndexType Top = 0;
            for (auto &I: Interpreter->InterpreterEnvironment->Heap.HeapData) {
                if (I.second.Marked) {
                    Top = std::max(Top, I.first);
                } else if (I.second.Kind == EnvObject::ObjectKind::ClassObject) {
                    if (I.second.Value.ClassObjectPointer->Members.count(builtin_has_code_before_destruct)) {
                        XIndexType AResult = static_cast<BytecodeInterpreterPool *>(Interpreter->Pool)->Allocate();
                        auto *NewInterpreter = &(*static_cast<BytecodeInterpreterPool *>(Interpreter->Pool))[AResult];
                        NewInterpreter->InterpreterEnvironment->Threads[AResult].Stack.FramesInformation.push_back(
                                {EnvironmentStackFramesInformation::FrameKind::FunctionStackFrame,
                                 0,
                                 0,
                                 {}});
                        XHeapIndexType FuncIdx = I.second.Value.ClassObjectPointer->Members[builtin_has_code_before_destruct];
                        NewInterpreter->InterpreterEnvironment->Threads[AResult].Stack.PushValueToStack(
                                {EnvironmentStackItem::ItemKind::HeapPointer,
                                 (EnvironmentStackItem::ItemValue) I.first});
                        NewInterpreter->InterpreterEnvironment->Threads[AResult].Stack.PushValueToStack(
                                {EnvironmentStackItem::ItemKind::HeapPointer,
                                 (EnvironmentStackItem::ItemValue) FuncIdx});
                        NewInterpreter->InstructionObjectLvalue2Rvalue(
                                (BytecodeStructure::InstructionParam) (XHeapIndexType) {});
                        NewInterpreter->InstructionFuncInvoke((BytecodeStructure::InstructionParam) (XIndexType) 1);
                        NewInterpreter->InterpreterEnvironment->Threads[AResult].PC.NowIndex++;
                        if (NewInterpreter->InterpreterEnvironment->Heap.HeapData[FuncIdx].Kind !=
                            EnvObject::ObjectKind::NativeMethodPointer) {
                            NewInterpreter->MainLoopInGC();
                        }
                        // pop the result
                        NewInterpreter->InterpreterEnvironment->Threads[AResult].Stack.PopValueFromStack();
                        NewInterpreter->InterpreterEnvironment->Threads[AResult].IsBusy = false;
                        NewInterpreter->IsBusy = false;
                    }
                }
            }

            std::set<void *> DoubleFreeFucker;
            for (auto Iter = Interpreter->InterpreterEnvironment->Heap.HeapData.begin();
                 Iter != Interpreter->InterpreterEnvironment->Heap.HeapData.end();) {
                auto I = *Iter;
                if (I.second.Marked) {
                    I.second.Marked = !I.second.Marked;
                } else {
                    switch (I.second.Kind) {
                        case EnvObject::ObjectKind::ArrayObject:
                        case EnvObject::ObjectKind::ClassObject:
                        case EnvObject::ObjectKind::StringObject:
                        case EnvObject::ObjectKind::BytesObject:
                        case EnvObject::ObjectKind::ClosurePointer: {
                            if (DoubleFreeFucker.count(static_cast<void *>(I.second.Value.ClassObjectPointer))) {
                                I.second = {};
                            } else {
                                DoubleFreeFucker.insert(static_cast<void *>(I.second.Value.ClassObjectPointer));
                                I.second.DestroyObject();
                                I.second = {};
                            }
                            if (I.first < Top)
                                Interpreter->InterpreterEnvironment->Heap.UsedIndexes.insert(I.first);
                            else {
                                Interpreter->InterpreterEnvironment->Heap.HeapData.erase(Iter++);
                                continue;
                            }
                            break;
                        }
                        default: {
                            I.second.DestroyObject();
                            I.second = {};
                            if (I.first < Top)
                                Interpreter->InterpreterEnvironment->Heap.UsedIndexes.insert(I.first);
                            else {
                                Interpreter->InterpreterEnvironment->Heap.HeapData.erase(Iter++);
                                continue;
                            }
                            break;
                        }
                    }
                }
                Iter++;
            }
            for (auto &I: Interpreter->InterpreterEnvironment->Heap.UsedIndexes) {
                Interpreter->InterpreterEnvironment->Heap.HeapData.erase(I);
            }

            // bugfix: 防止 UsedIndexes 集合過大
            Interpreter->InterpreterEnvironment->Heap.AllocatedElementCount = Top + 1;
            Limit = AAllocCount + EnvHeapGCStartCondition;
            Started = false;
            puts((std::to_string(Interpreter->InterpreterEnvironment->Heap.UsedIndexes.size()) + ", " +
                  std::to_string(Interpreter->InterpreterEnvironment->Heap.HeapData.size())).c_str());
        }
    }

    bool GarbageCollection::PassiveCheck() const {
        auto *Interpreter = static_cast<BytecodeInterpreter *>(InterpreterPointer);
        return Interpreter->InterpreterEnvironment->Heap.UsedIndexes.empty() &&
               Interpreter->InterpreterEnvironment->Heap.HeapData.size() >= EnvHeapDataAllocateSize / 2;
    }

    bool GarbageCollection::ActiveCheck() const {
        auto *Interpreter = static_cast<BytecodeInterpreter *>(InterpreterPointer);
        return Interpreter->InterpreterEnvironment->Heap.UsedIndexes.empty() &&
               Interpreter->InterpreterEnvironment->Heap.HeapData.size() >= Limit;
    }

    void GarbageCollection::ActiveGCThreadFunc(GarbageCollection &GC) {
        while (GC.ThreadFlag) {
            while (GC.ActiveCheck()) {
                InterpreterLock.lock();
                GC.Start(true);
                InterpreterLock.unlock();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
        }
    }

    void GarbageCollection::StopGCThread() {
        ThreadFlag = false;
        if (ActiveGCThread.joinable())
            ActiveGCThread.join();
    }

    GarbageCollection::~GarbageCollection() {
    }

    GarbageCollection::GarbageCollection(void *InterpreterPointer) : InterpreterPointer(InterpreterPointer) {
    }

    void GarbageCollection::StartGCThread() {
        ThreadFlag = true;
        ActiveGCThread = (std::thread) {ActiveGCThreadFunc, std::ref(*this)};
    }
} // XScript