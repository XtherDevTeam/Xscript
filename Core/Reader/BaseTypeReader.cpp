//
// Created by Jerry Chou on 2022/7/9.
//

#include "BaseTypeReader.hpp"
#include "../../Share/Utils.hpp"

namespace XScript {
    namespace Reader {
        BaseTypeReader::BaseTypeReader() {

        }

        XIndexType BaseTypeReader::ReadIndex(FILE *FilePointer) {
            XIndexType Result;
            fread(&Result, sizeof(XIndexType), 1, FilePointer);
            return Result;
        }

        XInteger BaseTypeReader::ReadInteger(FILE *FilePointer) {
            XInteger Result;
            fread(&Result, sizeof(XInteger), 1, FilePointer);
            return Result;
        }

        XDecimal BaseTypeReader::ReadDecimal(FILE *FilePointer) {
            XDecimal Result;
            fread(&Result, sizeof(XDecimal), 1, FilePointer);
            return Result;
        }

        XBoolean BaseTypeReader::ReadBoolean(FILE *FilePointer) {
            XBoolean Result;
            fread(&Result, sizeof(XBoolean), 1, FilePointer);
            return Result;
        }

        XString BaseTypeReader::ReadString(FILE *FilePointer) {
            XBytes Temp = ReadBytes(FilePointer);
            return string2wstring(Temp);
        }

        XBytes BaseTypeReader::ReadBytes(FILE *FilePointer) {
            XIndexType Idx = ReadIndex(FilePointer);
            XBytes Result;
            Result.resize(Idx);
            fread((void *) Result.data(), sizeof(char) * Idx, 1, FilePointer);
            return Result;
        }
    } // XScript
} // Reader