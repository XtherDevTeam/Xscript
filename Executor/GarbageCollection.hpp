//
// Created by chou on 22-7-19.
//

#ifndef XSCRIPT2_GARBAGECOLLECTION_HPP
#define XSCRIPT2_GARBAGECOLLECTION_HPP

#include "Environment.hpp"

namespace XScript {
    /**
     * When there are 256 elements in heap, start gc process.
     */
    constexpr XIndexType EnvHeapGCStartCondition = 256;

    class GarbageCollection {
        XIndexType Limit = 0 + EnvHeapGCStartCondition;
        Environment &Env;
    public:
        explicit GarbageCollection(Environment &Env);

        void Start();

        bool Check() const;
    };

} // XScript

#endif //XSCRIPT2_GARBAGECOLLECTION_HPP
