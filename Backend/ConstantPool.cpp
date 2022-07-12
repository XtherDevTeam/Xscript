//
// Created by Jerry Chou on 2022/6/17.
//

#include "ConstantPool.hpp"

namespace XScript {
    namespace Compiler {
        ConstantPool::ItemStructure::ItemStructure(XString StrVal) : Kind(ItemKind::StringVal),
                                                                     StrVal(std::move(StrVal)) {

        }

        bool ConstantPool::ItemStructure::operator==(const ItemStructure &rhs) const {
            if (Kind != rhs.Kind)
                return false;
            switch (Kind) {
                case ItemKind::StringVal:
                    return StrVal == rhs.StrVal;
            }
        }

        XIndexType ConstantPool::Push(const ConstantPool::ItemStructure &Structure) {
            XIndexType Idx = 0;
            for (auto &Item : Items) {
                if (Item == Structure) {
                    break;
                }
                Idx++;
            }
            Items.push_back(Structure);
            return Idx;
        }
    } // XScript
} // Compiler