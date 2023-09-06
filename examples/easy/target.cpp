#include "target.h"

bool target_fuzz(const uint8_t *data, size_t size)
{
	bool result = false;
	if (size >= 3)
	{
		result = data[0] == 'F' &&
			data[1] == 'U' &&
			data[2] == 'Z' &&
			data[3] == 'Z';
	}
	
	return result;
}
