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
    public:
        explicit GarbageCollection(Environment &Env);

        void Start();

        bool Check() const;
    };

} // XScript

#endif //XSCRIPT2_GARBAGECOLLECTION_HPP
