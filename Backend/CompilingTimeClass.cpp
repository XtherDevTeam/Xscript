//
// Created by Jerry Chou on 2022/5/21.
//

#include "CompilingTimeClass.hpp"

#include <utility>
#include <algorithm>

namespace XScript {
    namespace Compiler {
        CompilingTimeClass::CompilingTimeClass(const XArray<XIndexType> &parentClasses,
                                               XArray<XString> methods)
                : ParentClasses(
                parentClasses), Methods(std::move(methods)) {}

        void CompilingTimeClass::PushMethod(const XString &Name) {
            Methods.push_back(Name);
        }

        bool CompilingTimeClass::IsMethodExist(const XString &Name) {
            for (auto &I: Methods) {
                if (I == Name) return true;
            }
            return false;
        }
    } // XScript
} // Compiler