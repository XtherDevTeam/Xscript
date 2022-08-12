//
// Created by chou on 22-7-19.
//

#ifndef XSCRIPT2_GARBAGECOLLECTION_HPP
#define XSCRIPT2_GARBAGECOLLECTION_HPP

#include "Environment.hpp"

namespace XScript {
    class GarbageCollection {
        XIndexType Limit = 0 + EnvHeapGCStartCondition;
        Environment &Env;
        bool ThreadFlag;
        std::thread ActiveGCThread;
    public:
        explicit GarbageCollection(Environment &Env);

        void Start(bool force = false);

        bool PassiveCheck() const;

        bool ActiveCheck() const;

        static void ActiveGCThreadFunc(GarbageCollection &GC);

        GarbageCollection(GarbageCollection &copy) = delete;

        GarbageCollection(const GarbageCollection &copy) = delete;

        void Stop();
    };

} // XScript

#endif //XSCRIPT2_GARBAGECOLLECTION_HPP
