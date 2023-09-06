//===- FuzzerMain.cpp - main() function and flags -------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// main() and flags.
//===----------------------------------------------------------------------===//

#include "FuzzerDefs.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size);

extern "C" int FuzzerMain(int argc, char **argv)
{
  return fuzzer::FuzzerDriver(&argc, &argv, LLVMFuzzerTestOneInput);
}
