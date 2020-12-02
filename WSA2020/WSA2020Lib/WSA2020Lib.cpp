#include <iostream>

extern "C"
{
	int random(short a, short b)
	{
		return rand() % (b - a + 1) + a;
	}

	int length(char* str)
	{
		return strlen(str);
	}

	char* concat(char* str1, char* str2)
	{
		char* buf = new char[256];
		buf[0] = '\0';
		strcat_s(buf, 256, str1);
		strcat_s(buf + strlen(str1), 256, str2);
		return buf;
	}
}