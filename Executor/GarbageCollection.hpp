//
// Created by chou on 22-7-19.
//

#ifndef XSCRIPT2_GARBAGECOLLECTION_HPP
#define XSCRIPT2_GARBAGECOLLECTION_HPP

#include "Environment.hpp"
#include <thread>

namespace XScript {
    /**
     * When there are 256 elements in heap, start gc process.
     */
    constexpr XIndexType EnvHeapGCStartCondition = 256;

    class GarbageCollection {
        Environment &Env;
        std::thread GCThread;
    public:
        explicit GarbageCollection(Environment &Env);

        void Start();

        [[noreturn]] static void GCThreadFunc(GarbageCollection &This);

        void Init();
    };

} // XScript

#endif //XSCRIPT2_GARBAGECOLLECTION_HPP
