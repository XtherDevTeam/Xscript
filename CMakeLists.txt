cmake_minimum_required(VERSION 3.0)
project(Xscript2)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC_FILES
        "Frontend/*.cpp"
        "Frontend/Parsers/*.cpp"
        "Backend/*.cpp"
        "Backend/Compiler/*.cpp"
        "Executor/*.cpp"
        "Share/*.cpp"
        "Share/Exceptions/*.cpp"
        "Core/*.cpp"
        "Core/Serializatior/*.cpp"
        "Core/Reader/*.cpp"
        "NativeLibrary/*.cpp"
        )

add_executable(xsc Binary/Compiler/main.cpp ${SRC_FILES})
add_executable(xsvm Binary/Executor/main.cpp ${SRC_FILES})
add_executable(xnl-info Binary/XNativeLibraryInfo/main.cpp ${SRC_FILES})

if (CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
    TARGET_LINK_LIBRARIES(xsc dl)
    TARGET_LINK_LIBRARIES(xsvm dl)
    TARGET_LINK_LIBRARIES(xnl-info dl)
    TARGET_LINK_LIBRARIES(xsc pthread)
    TARGET_LINK_LIBRARIES(xsvm pthread)
    TARGET_LINK_LIBRARIES(xnl-info pthread)
elseif (CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
    set(CMAKE_EXE_LINKER_FLAGS "--static -lpthread")
endif ()

set(CMAKE_CXX_FLAGS_RELEASE "-O3")