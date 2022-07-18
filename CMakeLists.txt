cmake_minimum_required(VERSION 3.0)
project(Xscript2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

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

add_executable(Xscript2 main.cpp ${SRC_FILES})
