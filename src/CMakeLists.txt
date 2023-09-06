cmake_minimum_required(VERSION 3.7)
project(fuzzer)

set(CMAKE_BUILD_TYPE "RelWithDebInfo")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} /MT")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MT")

set(LIB_SOURCE_FILES FuzzerBuiltins.h FuzzerExtFunctionsDlsym.cpp FuzzerShmemWindows.cpp FuzzerBuiltinsMsvc.h FuzzerExtFunctionsWeak.cpp FuzzerMerge.cpp FuzzerTracePC.cpp FuzzerCommand.h FuzzerExtFunctionsWindows.cpp FuzzerMerge.h FuzzerTracePC.h FuzzerCorpus.h FuzzerExtraCounters.cpp FuzzerMutate.cpp FuzzerUtil.cpp FuzzerCrossOver.cpp FuzzerFlags.def FuzzerMutate.h FuzzerUtil.h FuzzerDataFlowTrace.cpp FuzzerInterface.h FuzzerOptions.h FuzzerUtilDarwin.cpp FuzzerDataFlowTrace.h FuzzerInternal.h FuzzerRandom.h FuzzerUtilFuchsia.cpp FuzzerDefs.h FuzzerIO.cpp FuzzerSHA1.cpp FuzzerUtilLinux.cpp FuzzerDictionary.h FuzzerIO.h FuzzerSHA1.h FuzzerUtilPosix.cpp FuzzerDriver.cpp FuzzerIOPosix.cpp FuzzerShmem.h FuzzerUtilWindows.cpp FuzzerExtFunctions.def FuzzerIOWindows.cpp FuzzerShmemFuchsia.cpp FuzzerValueBitMap.h FuzzerExtFunctions.h FuzzerLoop.cpp FuzzerShmemPosix.cpp FuzzerMain.cpp)

add_library(${PROJECT_NAME} STATIC ${LIB_SOURCE_FILES})

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(_output_suffix "_x64")
else()
	set(_output_suffix "_x86")
endif()

set_target_properties(${PROJECT_NAME}
	PROPERTIES
		OUTPUT_NAME "${PROJECT_NAME}${_output_suffix}")