//===- FuzzerDefs.h - Internal header for the Fuzzer ------------*- C++ -* ===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// Basic definitions.
//===----------------------------------------------------------------------===//

#ifndef LLVM_FUZZER_DEFS_H
#define LLVM_FUZZER_DEFS_H

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <memory>

#define LIBFUZZER_APPLE 0
#define LIBFUZZER_FUCHSIA 0
#define LIBFUZZER_LINUX 0
#define LIBFUZZER_NETBSD 0
#define LIBFUZZER_FREEBSD 0
#define LIBFUZZER_OPENBSD 0
#define LIBFUZZER_WINDOWS 1

#define LIBFUZZER_MSVC 1

#ifndef __has_attribute
#  define __has_attribute(x) 0
#endif

#define LIBFUZZER_POSIX                                                        \
  (LIBFUZZER_APPLE || LIBFUZZER_LINUX || LIBFUZZER_NETBSD ||                   \
   LIBFUZZER_FREEBSD || LIBFUZZER_OPENBSD)

#ifdef __x86_64
#  if __has_attribute(target)
#    define ATTRIBUTE_TARGET_POPCNT __attribute__((target("popcnt")))
#  else
#    define ATTRIBUTE_TARGET_POPCNT
#  endif
#else
#  define ATTRIBUTE_TARGET_POPCNT
#endif

//#define ATTRIBUTE_NO_SANITIZE_MEMORY __attribute__((no_sanitize("memory")))
#define ATTRIBUTE_NO_SANITIZE_MEMORY

//#define ALWAYS_INLINE __attribute__((always_inline))
#define ALWAYS_INLINE

//#define ATTRIBUTE_NO_SANITIZE_ADDRESS __attribute__((no_sanitize_address))
#define ATTRIBUTE_NO_SANITIZE_ADDRESS __declspec(no_sanitize_address)

#if defined(__has_feature)
#  if __has_feature(address_sanitizer)
#    define ATTRIBUTE_NO_SANITIZE_ALL ATTRIBUTE_NO_SANITIZE_ADDRESS
#  elif __has_feature(memory_sanitizer)
#    define ATTRIBUTE_NO_SANITIZE_ALL ATTRIBUTE_NO_SANITIZE_MEMORY
#  else
#    define ATTRIBUTE_NO_SANITIZE_ALL
#  endif
#else
#  define ATTRIBUTE_NO_SANITIZE_ALL
#endif

#define ATTRIBUTE_INTERFACE __declspec(dllexport)
// This is used for __sancov_lowest_stack which is needed for
// -fsanitize-coverage=stack-depth. That feature is not yet available on
// Windows, so make the symbol static to avoid linking errors.
/*
#define ATTRIBUTES_INTERFACE_TLS_INITIAL_EXEC \
  __attribute__((tls_model("initial-exec"))) thread_local static
*/
#define ATTRIBUTES_INTERFACE_TLS_INITIAL_EXEC static

namespace fuzzer {

    template <class T> T Min(T a, T b) { return a < b ? a : b; }
    template <class T> T Max(T a, T b) { return a > b ? a : b; }

    class Random;
    class Dictionary;
    class DictionaryEntry;
    class MutationDispatcher;
    struct FuzzingOptions;
    class InputCorpus;
    struct InputInfo;
    struct ExternalFunctions;

    // Global interface to functions that may or may not be available.
    extern ExternalFunctions* EF;

    // We are using a custom allocator to give a different symbol name to STL
    // containers in order to avoid ODR violations.
    template<typename T>
    class fuzzer_allocator : public std::allocator<T> {
    public:
        fuzzer_allocator() = default;

        template<class U>
        fuzzer_allocator(const fuzzer_allocator<U>&) {}

        template<class Other>
        struct rebind { typedef fuzzer_allocator<Other> other; };
    };

    template<typename T>
    using Vector = std::vector<T, fuzzer_allocator<T>>;

    template<typename T>
    using Set = std::set<T, std::less<T>, fuzzer_allocator<T>>;

    typedef Vector<uint8_t> Unit;
    typedef Vector<Unit> UnitVector;
    typedef int (*UserCallback)(const uint8_t* Data, size_t Size);

    int FuzzerDriver(int* argc, char*** argv, UserCallback Callback);

    uint8_t* ExtraCountersBegin();
    uint8_t* ExtraCountersEnd();
    void ClearExtraCounters();

    extern bool RunningUserCallback;

}  // namespace fuzzer

#endif  // LLVM_FUZZER_DEFS_H
