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

    EnvironmentStackItem::ItemValue::ItemValue(EnvFunction *FuncPointerVal) : FuncPointerVal(FuncPointerVal) {

    }

    EnvironmentStackItem::ItemValue::ItemValue(XHeapIndexType IdxVal) : HeapPointerVal(IdxVal) {

    }

    EnvironmentStackItem::EnvironmentStackItem(EnvironmentStackItem::ItemKind Kind,
                                               EnvironmentStackItem::ItemValue Value) : Kind(Kind), Value(Value) {

    }

    EnvironmentStackItem::EnvironmentStackItem() : Kind(ItemKind::Null), Value(static_cast<XHeapIndexType>(0)) {

    }

    XString EnvironmentStackItem::ToString() const {
        switch (Kind) {
            case ItemKind::Integer:
                return L"<XInteger value=" + std::to_wstring(Value.IntVal) + L">";
            case ItemKind::Decimal:
                return L"<XDecimal value=" + std::to_wstring(Value.DeciVal) + L">";
            case ItemKind::Boolean:
                return L"<XBoolean value=" + std::to_wstring(Value.BoolVal) + L">";
            case ItemKind::HeapPointer:
                return L"<XHeapPointer value=" + std::to_wstring(Value.HeapPointerVal) + L">";
            case ItemKind::FunctionPointer:
                return L"<XFunctionPointer value=" + std::to_wstring(Value.HeapPointerVal) + L">";
            case ItemKind::Null:
                return L"<XNull>";
        }
    }
} // XScript