//
// Created by Jerry Chou on 2022/5/21.
//

#include "CompilingTimeClass.hpp"

#include <utility>
#include <algorithm>

namespace XScript {
    namespace Compiler {
        CompilingTimeClass::CompilingTimeClass(const XString &ClassName, const ClassDescriptor &parentClass,
                                               XArray<std::pair<XString, XString>> methods)
                : ClassName(ClassName), ParentClass(parentClass), Methods(std::move(methods)) {}

        void CompilingTimeClass::PushMethod(const XString &Name, const XString &RealName) {
            Methods.push_back({Name, RealName});
        }

        // by real name
        XIndexType CompilingTimeClass::IsMethodExist(const XString &Name) {
            for (XIndexType Idx = 0; Idx < Methods.size(); Idx++) {
                if (Methods[Idx].second == Name) {
                    return Idx;
                }
            }
            return -1;
        }
    } // XScript
} // Compiler