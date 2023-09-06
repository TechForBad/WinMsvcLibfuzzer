cmake_minimum_required(VERSION 3.7)

project(fuzz_rapidxml)

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

# rapidxml sources
set(SOURCES_RAPIDXML "rapidxml.hpp;rapidxml_iterators.hpp;rapidxml_print.hpp;rapidxml_utils.hpp")

# fuzz executable
add_executable(fuzz_rapidxml fuzz_rapidxml.cpp ${SOURCES_RAPIDXML})
target_compile_options(fuzz_rapidxml PRIVATE ${COMPILE_OPTIONS})
target_link_directories(fuzz_rapidxml PRIVATE ${LLVM_LINK_DIRPATH})
target_link_libraries(fuzz_rapidxml PRIVATE ${LLVM_LINK_LIBRARIES_FOR_EXE})
target_link_options(fuzz_rapidxml PRIVATE ${LINK_OPTIONS_FOR_EXE})
