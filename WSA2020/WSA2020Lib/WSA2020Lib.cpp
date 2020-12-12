#include <iostream>


extern "C"
{
	int random(short a, short b)
	{
		return rand() % (a - b + 1) + b;
	}

	int len(short l, char* str)
	{
		int i = 0;
		int s = 0;
		while (str[i] != '\0')
		{
			s++;
			i++;
		}
		return s;
	}
	 
	char* concat(short l1, char* str1, short l2, char* str2)
	{
		char buf[256];
		int d = 0, s = 0;
		for (; str1[d] != '\0'; ++d)buf[d] = str1[d];
		for (; str2[s] != '\0'; ++s, ++d)buf[d] = str2[s];
		buf[d] = '\0';
		return buf;
	}

	bool writeNumberBin(short number)
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

		return true;
	}

	bool writeNumberOct(short number)
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
		return true;
	}
	

	bool  writeStr(short l, char* str)
	{
		std::cout << str << std::endl;
		return true;
	}

	bool writeBool(int b)
	{
		if (b < 1)std::cout << "false\n";
		else std::cout << "true\n";
		return true;
	}
		
}