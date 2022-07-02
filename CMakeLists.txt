cmake_minimum_required(VERSION 3.12)
project(Complier LANGUAGES CXX)

# 编译选项
SET(CFLAGS "")
SET(CMAKE_C_FLAGS "${CFLAGS}")




# 链接选项
set(LDFLAGS "")
set(CMAKE_EXE_LINKER_FLAGS    "${LDFLAGS}")

# 头文件路径
include_directories(Include)
include_directories(Include/LexicalAnalysis)

#源文件路径
add_subdirectory(Src)
add_subdirectory(Src/LexicalAnalysis)

add_executable(Compiler.exe)





target_link_libraries(Compiler.exe PUBLIC Main)
target_link_libraries(Compiler.exe PUBLIC DynString)
target_link_libraries(Compiler.exe PUBLIC DynArray)


add_custom_target(run
    COMMAND Compiler.exe
    WORKING_DIRECTORY .
)