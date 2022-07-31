//
// Created by Jerry Chou on 2022/5/14.
//

#ifndef XSCRIPT2_ENVOBJECT_HPP
#define XSCRIPT2_ENVOBJECT_HPP

#include "../Share/Config.hpp"
#include "EnvClassObject.hpp"
#include "EnvArrayObject.hpp"
#include "EnvStringObject.hpp"
#include "EnvFunction.hpp"
#include "../NativeLibrary/NativeLibrary.hpp"
#include "EnvBytesObject.hpp"

namespace XScript {

    class EnvObject {
    public:
        XBoolean Marked;

        enum class ObjectKind : XInteger {
            ClassObject,
            ArrayObject,
            StringObject,
            BytesObject,
            Integer,
            Decimal,
            Boolean,
            Index,
            FunctionPointer,
            NativeMethodPointer,
        } Kind;

        union ObjectValue {
            EnvClassObject *ClassObjectPointer;

            explicit ObjectValue(EnvClassObject *classObjectPointer);

            EnvArrayObject *ArrayObjectPointer;

            explicit ObjectValue(EnvArrayObject *arrayObjectPointer);

            EnvStringObject *StringObjectPointer;

            explicit ObjectValue(EnvStringObject *stringObjectPointer);

            EnvBytesObject *BytesObjectPointer;

            explicit ObjectValue(EnvBytesObject *bytesObjectPointer);

            XInteger IntegerValue{};

            explicit ObjectValue(XInteger integerValue);

            XDecimal DecimalValue;

            explicit ObjectValue(XDecimal decimalValue);

            XBoolean BooleanValue;

            explicit ObjectValue(XBoolean booleanValue);

            XIndexType IndexValue;

            explicit ObjectValue(XIndexType indexValue);

            EnvFunction *FunctionPointerValue;

            explicit ObjectValue(EnvFunction *functionPointerValue);

            NativeMethodInformation *NativeMethodPointerValue;

            explicit ObjectValue(NativeMethodInformation *nativeMethodPointerValue);
        } Value;

        EnvObject();

        EnvObject(ObjectKind Kind, ObjectValue Value);

        void DestroyObject() const;

        bool operator==(const EnvObject &RightHandSide) const;

        bool operator!=(const EnvObject &RightHandSide) const;
    };

} // XScript

#endif //XSCRIPT2_ENVOBJECT_HPP
