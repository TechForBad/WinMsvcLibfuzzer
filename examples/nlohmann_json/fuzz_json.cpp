#include <iostream>
#include <vector>

#include "json.hpp"

#define MY_TEST 0

#if MY_TEST
#define PRINT_LINE do{printf("line: %d\n", __LINE__);}while(0)
#else
#define PRINT_LINE
#endif

using json = nlohmann::json;

void test_parse(const uint8_t* data, size_t size)
{
	json json1;
	std::string str1;
	json json2;
	std::string str2;

	json1 = json::parse(data, data + size, nullptr, false, true);
	if (!json1.is_discarded())
	{
		str1 = json1.dump();
		json2 = json::parse(str1, nullptr, true, true);
		str2 = json2.dump();
		if (str1 != str2)
		{
			abort();
		}
	}
	
	json1 = json::parse(data, data + size, nullptr, false, false);
	if (!json1.is_discarded())
	{
		str1 = json1.dump();
		json2 = json::parse(str1, nullptr, true, false);
		str2 = json2.dump();
		if (str1 != str2)
		{
			abort();
		}
	}
}

void test_bson(const uint8_t* data, size_t size)
{
	json json1;
	json json2;
	std::vector<std::uint8_t> vec;

	json1 = json::from_bson(data, data + size, true, false);
	if (!json1.is_discarded())
	{
		vec = json::to_bson(json1);
		json2 = json::from_bson(vec, true, true);
		if (json::to_bson(json2) != vec)
		{
			abort();
		}
	}

	json1 = json::from_bson(data, data + size, false, false);
	if (!json1.is_discarded())
	{
		vec = json::to_bson(json1);
		json2 = json::from_bson(vec, false, true);
		if (json::to_bson(json2) != vec)
		{
			abort();
		}
	}
}

void test_cbor(const uint8_t* data, size_t size)
{
	json json1;
	json json2;
	std::vector<std::uint8_t> vec;

	json1 = json::from_cbor(data, data + size, true, false);
	if (!json1.is_discarded())
	{
		vec = json::to_cbor(json1);
		json2 = json::from_cbor(vec, true, true);
		if (json::to_cbor(json2) != vec)
		{
			abort();
		}
	}

	json1 = json::from_cbor(data, data + size, false, false);
	if (!json1.is_discarded())
	{
		vec = json::to_cbor(json1);
		json2 = json::from_cbor(vec, false, true);
		if (json::to_cbor(json2) != vec)
		{
			abort();
		}
	}
}

void test_msgpack(const uint8_t* data, size_t size)
{
	json json1;
	json json2;
	std::vector<std::uint8_t> vec;

	json1 = json::from_msgpack(data, data + size, true, false);
	if (!json1.is_discarded())
	{
		vec = json::to_msgpack(json1);
		json2 = json::from_msgpack(vec, true, true);
		if (json::to_msgpack(json2) != vec)
		{
			abort();
		}
	}

	json1 = json::from_msgpack(data, data + size, false, false);
	if (!json1.is_discarded())
	{
		vec = json::to_msgpack(json1);
		json2 = json::from_msgpack(vec, false, true);
		if (json::to_msgpack(json2) != vec)
		{
			abort();
		}
	}
}

void test_ubjson(const uint8_t* data, size_t size)
{
	json json1;
	json json2;
	std::vector<std::uint8_t> vec;

	json1 = json::from_ubjson(data, data + size, true, false);
	if (!json1.is_discarded())
	{
		vec = json::to_ubjson(json1);
		json2 = json::from_ubjson(vec, true, true);
		if (json::to_ubjson(json2) != vec)
		{
			abort();
		}
	}

	json1 = json::from_ubjson(data, data + size, false, false);
	if (!json1.is_discarded())
	{
		vec = json::to_ubjson(json1);
		json2 = json::from_ubjson(vec, false, true);
		if (json::to_ubjson(json2) != vec)
		{
			abort();
		}
	}
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t * data, size_t size)
{
	PRINT_LINE;
	test_parse(data, size);

	PRINT_LINE;
	test_bson(data, size);
	
	PRINT_LINE;
	test_cbor(data, size);
	
	PRINT_LINE;
	test_msgpack(data, size);
	
	PRINT_LINE;
	test_ubjson(data, size);

	return 0;
}

extern "C" int FuzzerMain(int argc, char **argv);

int main(int argc, char* argv[])
{
	return FuzzerMain(argc, argv);
}
