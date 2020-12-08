#include <iostream>


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
		int d = 0, s = 0;
		for (; d < l1; ++d)buf[d] = str1[d];
		for (; s < l2; ++s, ++d)buf[d] = str2[s];
		buf[d] = '\0';
		return buf;
	}

	void writeNumberBin(short number)
	{
		if (number < 0)std::cout << "1b" ;
		else std::cout << "0b" ;

		do
		{
			std::cout << number % 2;
			number /= 2;
		} while (number > 0);
		
		std::cout << std::endl;
	}

	void writeNumberOct(short number)
	{
		if (number < 0)std::cout << "1b";
		else std::cout << "0b";

		do
		{
			std::cout << number % 8;
			number /= 8;
		} while (number > 0);

		std::cout << std::endl;
	}

	void writeStr(char* str, short l)
	{
		std::cout << str << std::endl;
	}
	void writeBool(int b)
	{
		if (b < 1)std::cout << "false";
		else std::cout << "true";
	}
}