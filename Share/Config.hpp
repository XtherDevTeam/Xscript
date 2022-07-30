//
// Created by Jerry Chou on 2022/5/7.
//

#ifndef XSCRIPT2_CONFIG_HPP
#define XSCRIPT2_CONFIG_HPP

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <clocale>

namespace XScript {
    using XBytes = std::string;
    using XString = std::wstring;
    using XInteger = int64_t;
    using XDecimal = float;
    using XBoolean = bool;
    using XIndexType = uint64_t;
    using XCharacter = wchar_t;

    template<typename T> using XArray = std::vector<T>;
    template<typename T, typename T1> using XMap = std::map<T, T1>;

    using XHeapIndexType = XIndexType;

    constexpr XIndexType MaxThreadCount = 32;

    /**
     * Allocate 1024 elements when heap is created.
     */
    constexpr XIndexType EnvHeapDataAllocateSize = 1048576;

    /**
     * When there are 256 elements in heap, start gc process.
     */
    constexpr XIndexType EnvHeapGCStartCondition = 256;
} // XScript

#endif //XSCRIPT2_CONFIG_HPP
