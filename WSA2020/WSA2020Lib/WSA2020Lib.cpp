#include <iostream>


extern "C"
{
	int random(short a, short b)
	{
		return rand() % (a - b + 1) + b;
	}

	int len(short l, char* str)
	{
		return l;
	}
	 
	char* concat(short l1, char* str1, short l2, char* str2)
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
		int dest[16];
		int len = 0;
		do
		{
			dest[len] = number % 2;
			number /= 2;
			len++;
		} while (number > 0);
		len--;

		for (; len >= 0; --len)std::cout << dest[len];
		
		std::cout << std::endl;
	}

	void writeNumberOct(short number)
	{
		if (number < 0)std::cout << "1o";
		else std::cout << "0o";
		int dest[16];
		int len = 0;
		do
		{
			dest[len] = number % 8;
			number /= 8;
			len++;
		} while (number > 0);
		len--;

		for (; len >= 0; --len)std::cout << dest[len];

		std::cout << std::endl;
	}
	

	void  writeStr(short l, char* str)
	{
		std::cout << str << std::endl;

	}

	void writeBool(int b)
	{
		if (b < 1)std::cout << "false";
		else std::cout << "true";
	}
		
}