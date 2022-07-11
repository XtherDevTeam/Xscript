//
// Created by Jerry Chou on 2022/5/31.
//

#include "BaseTypeSerializatior.hpp"
#include "../../Share/Exceptions/InternalException.hpp"

namespace XScript {
    namespace Serializatior {
        BaseTypeSerializatior::BaseTypeSerializatior() {

        }

        void BaseTypeSerializatior::operator()(FILE *FilePointer, XInteger Integer) {
            if (fwrite(&Integer, sizeof(XInteger), 1, FilePointer) == -1) {
                throw InternalException(L"BaseTypeSerializatior: Cannot write to file.");
            }
        }

        void BaseTypeSerializatior::operator()(FILE *FilePointer, XDecimal Decimal) {
            if (fwrite(&Decimal, sizeof(XDecimal), 1, FilePointer) == -1) {
                throw InternalException(L"BaseTypeSerializatior: Cannot write to file.");
            }
        }

        void BaseTypeSerializatior::operator()(FILE *FilePointer, XBoolean Boolean) {
            if (fwrite(&Boolean, sizeof(Boolean), 1, FilePointer) == -1) {
                throw InternalException(L"BaseTypeSerializatior: Cannot write to file.");
            }
        }

        void BaseTypeSerializatior::operator()(FILE *FilePointer, const XString &String) {
            XBytes Bytes = wstring2string(String);
            operator()(FilePointer, static_cast<XIndexType>(String.length()));
            if (fwrite(Bytes.c_str(), Bytes.size(), 1, FilePointer) == -1) {
                throw InternalException(L"BaseTypeSerializatior: Cannot write to file.");
            }
        }

        void BaseTypeSerializatior::operator()(FILE *FilePointer, const XBytes &String) {
            operator()(FilePointer, static_cast<XIndexType>(String.length()));
            if (fwrite(String.c_str(), String.size(), 1, FilePointer) == -1) {
                throw InternalException(L"BaseTypeSerializatior: Cannot write to file.");
            }
        }

        void BaseTypeSerializatior::operator()(FILE *FilePointer, XIndexType Index) {
            if (fwrite(&Index, sizeof(Index), 1, FilePointer) == -1) {
                throw InternalException(L"BaseTypeSerializatior: Cannot write to file.");
            }
        }
    } // XScript
} // Serializatior