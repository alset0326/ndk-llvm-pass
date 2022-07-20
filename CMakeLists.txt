cmake_minimum_required(VERSION 3.23)
project(ndk-llvm-sample-pass)

set(CMAKE_CXX_STANDARD 14)

# we need LLVM_HOME in order to automatically set LLVM_DIR
if (NOT DEFINED ENV{LLVM_HOME})
    message(FATAL_ERROR "$LLVM_HOME is not defined")
endif ()
if (NOT DEFINED ENV{LLVM_DIR})
    set(ENV{LLVM_DIR} $ENV{LLVM_HOME}/lib64/cmake/llvm)
endif ()

# we make compiler same as our target
set(CMAKE_C_COMPILER $ENV{LLVM_HOME}/bin/clang)
set(CMAKE_CXX_COMPILER $ENV{LLVM_HOME}/bin/clang++)

find_package(LLVM REQUIRED CONFIG)

separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})
include_directories(${LLVM_INCLUDE_DIRS})

add_subdirectory(NdkSamplePass)
