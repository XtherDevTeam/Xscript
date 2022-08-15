//
// Created by chou on 22-7-19.
//

#ifndef XSCRIPT2_GARBAGECOLLECTION_HPP
#define XSCRIPT2_GARBAGECOLLECTION_HPP

#include "Environment.hpp"

namespace XScript {
    class GarbageCollection {
        XIndexType Limit = 0 + EnvHeapGCStartCondition;
        bool ThreadFlag;
        std::thread ActiveGCThread;
    public:
        void *InterpreterPointer;

        explicit GarbageCollection(void *InterpreterPointer);

        void Start(bool force = false);

        [[nodiscard]] bool PassiveCheck() const;

        [[nodiscard]] bool ActiveCheck() const;

        static void ActiveGCThreadFunc(GarbageCollection &GC);

        GarbageCollection(GarbageCollection &copy) = delete;

        GarbageCollection(const GarbageCollection &copy) = delete;

        void Stop();

        ~GarbageCollection();
    };

} // XScript

#endif //XSCRIPT2_GARBAGECOLLECTION_HPP
