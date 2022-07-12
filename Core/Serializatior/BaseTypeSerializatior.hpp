//
// Created by Jerry Chou on 2022/5/31.
//

#ifndef XSCRIPT2_BASETYPESERIALIZATIOR_HPP
#define XSCRIPT2_BASETYPESERIALIZATIOR_HPP

#include "../../Share/Utils.hpp"

namespace XScript {
    namespace Serializatior {

        class BaseTypeSerializatior {
        public:
            BaseTypeSerializatior();

            void operator()(FILE *FilePointer, XIndexType Index);

            void operator()(FILE *FilePointer, XInteger Integer);

            void operator()(FILE *FilePointer, XDecimal Decimal);

            void operator()(FILE *FilePointer, XBoolean Boolean);

            void operator()(FILE *FilePointer, const XString &String);

            void operator()(FILE *FilePointer, const XBytes &String);
        };

    } // XScript
} // Serializatior

#endif //XSCRIPT2_BASETYPESERIALIZATIOR_HPP
