//
// Created by Jerry Chou on 2022/7/9.
//

#ifndef XSCRIPT2_ENVCONSTANTPOOL_HPP
#define XSCRIPT2_ENVCONSTANTPOOL_HPP

#include "../Share/Config.hpp"

namespace XScript {

    class EnvConstantPool {
    public:
        class EnvConstant {
        public:
            enum class ItemKind : XInteger {
                StringVal
            } Kind;

            XString Value;
        };

        XArray<EnvConstant> Constants;

        EnvConstant & operator[](XIndexType Index);
    };

} // XScript

#endif //XSCRIPT2_ENVCONSTANTPOOL_HPP
