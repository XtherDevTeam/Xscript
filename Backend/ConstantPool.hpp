//
// Created by Jerry Chou on 2022/6/17.
//

#ifndef XSCRIPT2_CONSTANTPOOL_HPP
#define XSCRIPT2_CONSTANTPOOL_HPP

#include "../Share/Config.hpp"

namespace XScript {
    namespace Compiler {

        class ConstantPool {
        public:
            class ItemStructure {
            public:
                enum class ItemKind : XInteger {
                    StringVal,
                } Kind;
                XString StrVal;

                explicit ItemStructure(XString StrVal);

                bool operator==(const ItemStructure &rhs) const;
            };

            XArray<ItemStructure> Items;

            XIndexType Push(const ItemStructure &Structure);
        };

    } // XScript
} // Compiler

#endif //XSCRIPT2_CONSTANTPOOL_HPP
