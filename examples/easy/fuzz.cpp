#include "target.h"

extern "C" int FuzzerMain(int argc, char **argv);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	target_fuzz(data, size);
	
	return 0;
}

int main(int argc, char* argv[])
{
	return FuzzerMain(argc, argv);
}
