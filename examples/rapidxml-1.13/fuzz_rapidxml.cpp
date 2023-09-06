#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

#include <Windows.h>

using namespace rapidxml;

#define MY_TEST 0

#if MY_TEST
#define PRINT_LINE do{printf("line: %d\n", __LINE__);}while(0)
#else
#define PRINT_LINE
#endif

extern "C" int LLVMFuzzerTestOneInput(const uint8_t * data, size_t size)
{
	xml_document<> doc;
	std::string str;

	if (size <= 0)
	{
		goto End;
	}

	str.resize(size + 1);
	memcpy((char*)str.data(), data, size);
	str[size] = '\0';

	try
	{
		doc.parse<parse_no_data_nodes>((char*)str.data());
		doc.parse<parse_no_element_values>((char*)str.data());
		doc.parse<parse_no_string_terminators>((char*)str.data());
		doc.parse<parse_no_entity_translation>((char*)str.data());
		doc.parse<parse_no_utf8>((char*)str.data());
		doc.parse<parse_declaration_node>((char*)str.data());
		doc.parse<parse_comment_nodes>((char*)str.data());
		doc.parse<parse_doctype_node>((char*)str.data());
		doc.parse<parse_pi_nodes>((char*)str.data());
		doc.parse<parse_validate_closing_tags>((char*)str.data());
		doc.parse<parse_trim_whitespace>((char*)str.data());
		doc.parse<parse_normalize_whitespace>((char*)str.data());

		doc.parse<parse_default>((char*)str.data());
		doc.parse<parse_non_destructive>((char*)str.data());
		doc.parse<parse_fastest>((char*)str.data());
		doc.parse<parse_full>((char*)str.data());
	}
	catch (parse_error& e)
	{

	}
	catch (...)
	{
		abort();
	}

End:
	return 0;
}

extern "C" int FuzzerMain(int argc, char **argv);

int main(int argc, char* argv[])
{
	return FuzzerMain(argc, argv);
}
