//
// Created by Jerry Chou on 2022/5/13.
//

#ifndef XSCRIPT2_ENVIRONMENTSTACKITEM_HPP
#define XSCRIPT2_ENVIRONMENTSTACKITEM_HPP

#include "../Share/Utils.hpp"
#include "EnvFunction.hpp"
#include "../NativeLibrary/NativeLibrary.hpp"


namespace XScript {

    class EnvironmentStackItem {

    public:
        enum class ItemKind : XInteger {
            Integer,
            Decimal,
            Boolean,
            HeapPointer,
            FunctionPointer,
            NativeMethodPointer,
            Null,
        } Kind;

        union ItemValue {
            XInteger IntVal;
            XDecimal DeciVal;
            XBoolean BoolVal;
            XHeapIndexType HeapPointerVal;
            EnvFunction *FuncPointerVal;
            NativeMethodInformation *NativeMethodPointerVal;


            explicit ItemValue(XInteger IntVal);

            explicit ItemValue(XDecimal DeciVal);

            explicit ItemValue(XBoolean BoolVal);

            explicit ItemValue(XHeapIndexType HeapPointerVal);

            explicit ItemValue(EnvFunction *FuncPointerVal);

            explicit ItemValue(NativeMethodInformation *NativeMethodPointerVal);
        } Value;

        EnvironmentStackItem();

        EnvironmentStackItem(ItemKind Kind, ItemValue Value);

        [[nodiscard]] XString ToString() const;
    };

} // XScript


#endif //XSCRIPT2_ENVIRONMENTSTACKITEM_HPP
