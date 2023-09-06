cmake_minimum_required(VERSION 3.7)
project(easy)

set(CMAKE_BUILD_TYPE "RelWithDebInfo")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} /MT /Zi")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MT /Zi")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(LLVM_LINK_DIRPATH "${CMAKE_CURRENT_SOURCE_DIR}\\..\\..\\fuzzer_lib\\x64")
	set(COMPILE_OPTIONS "/fsanitize=address;/d2Sancov;/fsanitize-coverage=inline-8bit-counters")
	set(LLVM_LINK_LIBRARIES_FOR_EXE "libsancov.lib;fuzzer_x64.lib")
	set(LINK_OPTIONS_FOR_EXE "/wholearchive:clang_rt.asan-x86_64.lib;/wholearchive:clang_rt.asan_cxx-x86_64.lib;/wholearchive:fuzzer_x64.lib;/debug;/LTCG:OFF;/incremental:no")
	set(LLVM_LINK_LIBRARIES_FOR_DLL "libsancov.lib;clang_rt.asan_dll_thunk-x86_64.lib")
	set(LINK_OPTIONS_FOR_DLL "/wholearchive:clang_rt.asan_dll_thunk-x86_64.lib;/LTCG:OFF;/incremental:no")
else()
	set(LLVM_LINK_DIRPATH "${CMAKE_CURRENT_SOURCE_DIR}\\..\\..\\fuzzer_lib\\win32")
	set(COMPILE_OPTIONS "/fsanitize=address;/d2Sancov;/fsanitize-coverage=inline-8bit-counters")
	set(LLVM_LINK_LIBRARIES_FOR_EXE "libsancov.lib;fuzzer_x86.lib")
	set(LINK_OPTIONS_FOR_EXE "/wholearchive:clang_rt.asan-i386.lib;/wholearchive:clang_rt.asan_cxx-i386.lib;/wholearchive:fuzzer_x86.lib;/debug;/LTCG:OFF;/incremental:no")
	set(LLVM_LINK_LIBRARIES_FOR_DLL "libsancov.lib;clang_rt.asan_dll_thunk-i386.lib")
	set(LINK_OPTIONS_FOR_DLL "/wholearchive:clang_rt.asan_dll_thunk-i386.lib;/LTCG:OFF;/incremental:no")
endif()

# fuzz executable
add_executable(fuzz_exe fuzz.cpp target.h target.cpp)
target_compile_options(fuzz_exe PRIVATE ${COMPILE_OPTIONS})
target_link_directories(fuzz_exe PRIVATE ${LLVM_LINK_DIRPATH})
target_link_libraries(fuzz_exe PRIVATE ${LLVM_LINK_LIBRARIES_FOR_EXE})
target_link_options(fuzz_exe PRIVATE ${LINK_OPTIONS_FOR_EXE})

# fuzz static library
add_library(target_lib STATIC target.h target.cpp)
target_compile_options(target_lib PRIVATE ${COMPILE_OPTIONS})

add_executable(fuzz_lib fuzz.cpp target.h)
target_link_libraries(fuzz_lib PRIVATE target_lib)
target_compile_options(fuzz_lib PRIVATE ${COMPILE_OPTIONS})
target_link_directories(fuzz_lib PRIVATE ${LLVM_LINK_DIRPATH})
target_link_libraries(fuzz_lib PRIVATE ${LLVM_LINK_LIBRARIES_FOR_EXE})
target_link_options(fuzz_lib PRIVATE ${LINK_OPTIONS_FOR_EXE})

# fuzz dynamic library
add_library(target_dll SHARED target.h target.cpp)
target_compile_options(target_dll PRIVATE ${COMPILE_OPTIONS})
target_link_directories(target_dll PRIVATE ${LLVM_LINK_DIRPATH})
target_link_libraries(target_dll PRIVATE ${LLVM_LINK_LIBRARIES_FOR_DLL})
target_link_options(target_dll PRIVATE ${LINK_OPTIONS_FOR_DLL})

add_executable(fuzz_dll fuzz.cpp target.h)
target_link_libraries(fuzz_dll PRIVATE target_dll)
target_compile_options(fuzz_dll PRIVATE ${COMPILE_OPTIONS})
target_link_directories(fuzz_dll PRIVATE ${LLVM_LINK_DIRPATH})
target_link_libraries(fuzz_dll PRIVATE ${LLVM_LINK_LIBRARIES_FOR_EXE})
target_link_options(fuzz_dll PRIVATE ${LINK_OPTIONS_FOR_EXE})
