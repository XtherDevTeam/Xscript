//
// Created by Jerry Chou on 2022/7/9.
//

#ifndef XSCRIPT2_BASETYPEREADER_HPP
#define XSCRIPT2_BASETYPEREADER_HPP

#include "../../Share/Config.hpp"

namespace XScript {
    namespace Reader {

        class BaseTypeReader {
        public:
            BaseTypeReader();

            XIndexType ReadIndex(FILE *FilePointer);

            XInteger ReadInteger(FILE *FilePointer);

            XDecimal ReadDecimal(FILE *FilePointer);

            XBoolean ReadBoolean(FILE *FilePointer);

            XString ReadString(FILE *FilePointer);

            XBytes ReadBytes(FILE *FilePointer);
        };

    } // XScript
} // Reader

#endif //XSCRIPT2_BASETYPEREADER_HPP
