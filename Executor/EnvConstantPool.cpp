//
// Created by Jerry Chou on 2022/7/9.
//

#include "EnvConstantPool.hpp"

namespace XScript {
    EnvConstantPool::EnvConstant &EnvConstantPool::operator[](XIndexType Index) {
        return Constants[Index];
    }
} // XScript