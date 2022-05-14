//
// Created by Jerry Chou on 2022/5/14.
//

#include "EnvObject.hpp"

namespace XScript {
    EnvObject::ObjectValue::ObjectValue(EnvClassObject *classObjectPointer) : ClassObjectPointer(classObjectPointer) {}

    EnvObject::ObjectValue::ObjectValue(EnvArrayObject *arrayObjectPointer) : ArrayObjectPointer(arrayObjectPointer) {}

    EnvObject::ObjectValue::ObjectValue(EnvStringObject *stringObjectPointer) : StringObjectPointer(
            stringObjectPointer) {}

    EnvObject::ObjectValue::ObjectValue(XInteger integerValue) : IntegerValue(integerValue) {}

    EnvObject::ObjectValue::ObjectValue(XDecimal decimalValue) : DecimalValue(decimalValue) {}

    EnvObject::ObjectValue::ObjectValue(XBoolean booleanValue) : BooleanValue(booleanValue) {}

    EnvObject::EnvObject() : Kind(ObjectKind::Integer), Value(static_cast<XInteger>(0)) {

    }

    EnvObject::EnvObject(EnvObject::ObjectKind Kind, EnvObject::ObjectValue Value) : Kind(Kind), Value(Value) {

    }

    void EnvObject::DestroyObject() const {
        switch (Kind) {
            case ObjectKind::ClassObject:
                /* TODO: Add classes to XScript2 */
                break;
            case ObjectKind::ArrayObject:
                FreeEnvArrayObject(Value.ArrayObjectPointer);
                break;
            case ObjectKind::StringObject:
                FreeEnvStringObject(Value.StringObjectPointer);
                break;
            case ObjectKind::Integer:
            case ObjectKind::Decimal:
            case ObjectKind::Boolean:
                break;
        }
    }
} // XScript