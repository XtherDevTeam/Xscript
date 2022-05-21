//
// Created by Jerry Chou on 2022/5/21.
//

#include "CompilerError.hpp"

namespace XScript {
    CompilerError::CompilerError(XIndexType Line, XIndexType Col, const XString &Text) : XScriptException(
            L"[CompilerError] At line " + std::to_wstring(Line) + L" column " + std::to_wstring(Col) + L" : " + Text) {
    }
} // XScript