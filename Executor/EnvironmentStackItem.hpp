//
// Created by Jerry Chou on 2022/5/13.
//

#ifndef XSCRIPT2_ENVIRONMENTSTACKITEM_HPP
#define XSCRIPT2_ENVIRONMENTSTACKITEM_HPP

#include "../Share/Utils.hpp"


namespace XScript {

    class EnvironmentStackItem {

    public:
        enum class ItemKind : XInteger {
            Integer,
            Decimal,
            Boolean,
            HeapPointer,
            Null,
        } Kind;

        union ItemValue {
            XInteger IntVal;
            XDecimal DeciVal;
            XBoolean BoolVal;
            XHeapIndexType HeapPointerVal;

            explicit ItemValue(XInteger IntVal);

            explicit ItemValue(XDecimal DeciVal);

            explicit ItemValue(XBoolean BoolVal);

            explicit ItemValue(XHeapIndexType IdxVal);
        } Value;

        EnvironmentStackItem();

        EnvironmentStackItem(ItemKind Kind, ItemValue Value);

        XString ToString() const;
    };

} // XScript


#endif //XSCRIPT2_ENVIRONMENTSTACKITEM_HPP
