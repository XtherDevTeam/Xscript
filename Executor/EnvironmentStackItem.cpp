//
// Created by Jerry Chou on 2022/5/13.
//

#include "EnvironmentStackItem.hpp"

namespace XScript {

    EnvironmentStackItem::ItemValue::ItemValue(XInteger IntVal) : IntVal(IntVal) {

    }

    EnvironmentStackItem::ItemValue::ItemValue(XDecimal DeciVal) : DeciVal(DeciVal) {

    }

    EnvironmentStackItem::ItemValue::ItemValue(XBoolean BoolVal) : BoolVal(BoolVal) {

    }

    EnvironmentStackItem::ItemValue::ItemValue(XHeapIndexType IdxVal) : HeapPointerVal(IdxVal) {

    }

    EnvironmentStackItem::EnvironmentStackItem(EnvironmentStackItem::ItemKind Kind,
                                               EnvironmentStackItem::ItemValue Value) : Kind(Kind), Value(Value) {

    }

    EnvironmentStackItem::EnvironmentStackItem() : Kind(ItemKind::Null), Value(static_cast<XHeapIndexType>(0)) {

    }
} // XScript