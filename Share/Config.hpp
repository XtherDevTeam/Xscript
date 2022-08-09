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
    using XDecimal = double;
    using XBoolean = bool;
    using XIndexType = uint64_t;
    using XCharacter = wchar_t;

    template<typename T> using XArray = std::vector<T>;
    template<typename T, typename T1> using XMap = std::map<T, T1>;

    using XHeapIndexType = XIndexType;

    constexpr XIndexType MaxThreadCount = 64;

    /**
     * Allocate 1024 elements when heap is created.
     */
    constexpr XIndexType EnvHeapDataAllocateSize = 536870912;

    /**
     * When there are 256 elements in heap, start gc process.
     */
    constexpr XIndexType EnvHeapGCStartCondition = 256;

#ifdef XSCRIPT2_COMMIT_VERSION
    constexpr const wchar_t* CommitVersion = XSCRIPT2_COMMIT_VERSION;
#endif
} // XScript

#if defined(_WIN32)
#define DynamicLibraryPostfix L".dll"
#elif defined(__linux__)
#define DynamicLibraryPostfix L".so"
#elif defined(__APPLE__)
#define DynamicLibraryPostfix L".dylib"
#else
#define DynamicLibraryPostfix L""
#endif

#endif //XSCRIPT2_CONFIG_HPP
