#include "StringUtils.h"

size_t strLength(const char* str)
{
	int length = 0;
	while (*str)
	{
		++length;
		++str;
	}
	return length;
}

char* strCopy(char* dest, const char* src)
{
	char* copyDest = dest;
	while (*src)
	{
		*dest = *src;
		++src;
		++dest;
	}
	*dest = '\0';
	return copyDest;
}

