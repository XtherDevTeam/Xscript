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

    EnvObject::ObjectValue::ObjectValue(EnvFunction *functionPointerValue) : FunctionPointerValue(
            functionPointerValue) {}

    EnvObject::ObjectValue::ObjectValue(XIndexType indexValue) : IndexValue(indexValue) {}

    EnvObject::ObjectValue::ObjectValue(NativeMethodInformation *nativeMethodPointerValue) : NativeMethodPointerValue(
            nativeMethodPointerValue) {}

    EnvObject::ObjectValue::ObjectValue(EnvBytesObject *bytesObjectPointer) : BytesObjectPointer(bytesObjectPointer) {

    }

    EnvObject::ObjectValue::ObjectValue(EnvClosureObject *closurePointer) : ClosurePointer(closurePointer) {

    }

    EnvObject::EnvObject() : Marked(false), Kind(ObjectKind::Integer), Value(static_cast<XInteger>(0)) {

    }

    EnvObject::EnvObject(EnvObject::ObjectKind Kind, EnvObject::ObjectValue Value) : Marked(false), Kind(Kind),
                                                                                     Value(Value) {

    }

    void EnvObject::DestroyObject() const {
        CreatedUnfreeElement--;
        switch (Kind) {
            case ObjectKind::ClassObject:
                FreeEnvClassObject(Value.ClassObjectPointer);
                break;
            case ObjectKind::ArrayObject:
                FreeEnvArrayObject(Value.ArrayObjectPointer);
                break;
            case ObjectKind::StringObject:
                FreeEnvStringObject(Value.StringObjectPointer);
                break;
            case ObjectKind::BytesObject:
                FreeEnvBytesObject(Value.BytesObjectPointer);
                break;
            case ObjectKind::ClosurePointer:
                FreeEnvClosureObject(Value.ClosurePointer);
                break;
            default:
                break;
        }
    }

    bool EnvObject::operator==(const EnvObject &RightHandSide) const {
        if (RightHandSide.Kind != Kind) return false;
        switch (Kind) {
            case ObjectKind::ClassObject:
                /* TODO: Add classes to XScript 2 */
                break;
            case ObjectKind::ArrayObject:
                if (Value.ArrayObjectPointer->Length() != RightHandSide.Value.ArrayObjectPointer->Length())
                    return false;
                for (auto Left = Value.ArrayObjectPointer->Elements.begin(), Right = RightHandSide.Value.ArrayObjectPointer->Elements.begin();
                     Left != Value.ArrayObjectPointer->Elements.end(); ++Left, ++Right) {
                    if (*Left != *Right)
                        return false;
                }
                return true;
            case ObjectKind::StringObject:
                if (Value.StringObjectPointer->Length != RightHandSide.Value.StringObjectPointer->Length) return false;
                for (auto Left = &Value.StringObjectPointer->Dest, Right = &RightHandSide.Value.StringObjectPointer->Dest;
                     Left != &Value.StringObjectPointer->Dest + Value.StringObjectPointer->Length; ++Left, ++Right) {
                    if (*Left != *Right)
                        return false;
                }
                return true;
            case ObjectKind::Integer:
            case ObjectKind::Decimal:
            case ObjectKind::Boolean:
                return Value.IntegerValue == RightHandSide.Value.IntegerValue;
        }
        return false;
    }

    bool EnvObject::operator!=(const EnvObject &RightHandSide) const {
        return !((*this) == RightHandSide);
    }
} // XScript