//
// Created by Jerry Chou on 2022/5/21.
//

#include "CompilingTimeClass.hpp"

#include <utility>
#include <algorithm>

namespace XScript {
    namespace Compiler {
        CompilingTimeClass::CompilingTimeClass(const XString &Name, const XArray <ClassDescriptor> &parentClasses,
                                               XArray<XString> methods)
                : ClassName(Name), ParentClasses(parentClasses), Methods(std::move(methods)) {}

        void CompilingTimeClass::PushMethod(const XString &Name) {
            Methods.push_back(Name);
        }

        XIndexType CompilingTimeClass::IsMethodExist(const XString &Name) {
            for (XIndexType Idx = 0; Idx < Methods.size(); Idx++) {
                if (Methods[Idx] == Name) {
                    return Idx;
                }
            }
            return -1;
        }
    } // XScript
} // Compiler