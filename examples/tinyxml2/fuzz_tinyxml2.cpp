#include "tinyxml2.h"

#include <cerrno>
#include <cstdlib>

using namespace tinyxml2;

#define MY_TEST 0

#if MY_TEST
#define PRINT_LINE do{printf("line: %d\n", __LINE__);}while(0)
#else
#define PRINT_LINE
#endif

extern "C" int LLVMFuzzerTestOneInput(const char* data, size_t size)
{
	XMLDocument doc;
	XMLError result;
	XMLPrinter printer;

	//doc进行解析
	result = doc.Parse(data, size);

	//doc可能会解析失败
	if (XML_SUCCESS != result)
	{
		goto End;
	}

	//doc打印到printer
	doc.Print(&printer);

End:
	return 0;
}

extern "C" int FuzzerMain(int argc, char **argv);

int main(int argc, char* argv[])
{
	return FuzzerMain(argc, argv);
}
