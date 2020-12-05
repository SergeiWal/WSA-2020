#include <iostream>
#include <string>

extern "C"
{
	int random(short a, short b)
	{
		return rand() % (b - a + 1) + a;
	}

	int len(char* str, short l)
	{
		return l;
	}

	char* concat(char* str1, short l1, char* str2, short l2)
	{
		char* buf = new char[256];
		buf[0] = '\0';
		strcat_s(buf, 256, str1);
		strcat_s(buf + strlen(str1), 256, str2);
		return buf;
	}

	void writeNumberBin(short number)
	{
		bool isSign = false;
		std::string result;
		if (number < 0)isSign = true;
		do
		{
			result = std::to_string(number % 2) + result;
		} while (number > 0);
		if (isSign)result = "1b" + result;
		else result = "0b" + result;
		std::cout << result << std::endl;
	}

	void writeNumberOct(short number)
	{
		bool isSign = false;
		std::string result;
		if (number < 0)isSign = true;
		do
		{
			result = std::to_string(number % 8) + result;
		} while (number > 0);
		if (isSign)result = "1o" + result;
		else result = "0o" + result;
		std::cout << result << std::endl;
	}

	void writeStr(char* str, short l)
	{
		std::cout << str << std::endl;
	}
}