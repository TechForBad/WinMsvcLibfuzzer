#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

extern "C" __declspec(dllexport) bool target_fuzz(const uint8_t *data, size_t size);
