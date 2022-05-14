//
// Created by Jerry Chou on 2022/5/14.
//

#ifndef XSCRIPT2_ENVOBJECT_HPP
#define XSCRIPT2_ENVOBJECT_HPP

#include "../Share/Config.hpp"
#include "EnvClassObject.hpp"
#include "EnvArrayObject.hpp"
#include "EnvStringObject.hpp"

namespace XScript {

    class EnvObject {
    public:
        enum class ObjectKind : XInteger {
            ClassObject,
            ArrayObject,
            StringObject,
            Integer,
            Decimal,
            Boolean,
        } Kind;

        union ObjectValue {
            explicit ObjectValue(EnvClassObject *classObjectPointer);

            EnvClassObject *ClassObjectPointer;
            EnvArrayObject *ArrayObjectPointer;

            explicit ObjectValue(EnvArrayObject *arrayObjectPointer);

            EnvStringObject *StringObjectPointer;

            explicit ObjectValue(EnvStringObject *stringObjectPointer);

            XInteger IntegerValue{};

            explicit ObjectValue(XInteger integerValue);

            XDecimal DecimalValue;

            explicit ObjectValue(XDecimal decimalValue);

            XBoolean BooleanValue;

            explicit ObjectValue(XBoolean booleanValue);
        } Value;

        EnvObject();

        EnvObject(ObjectKind Kind, ObjectValue Value);

        void DestroyObject() const;
    };

} // XScript

#endif //XSCRIPT2_ENVOBJECT_HPP
