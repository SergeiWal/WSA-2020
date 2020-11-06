#include "In.h"


namespace In {

	IN getin(wchar_t infile[])
	{
		IN in;
		std::ifstream input;
		input.open(infile);
		if (!input.is_open())throw ERROR_THROW(110);

		in.lines = 0;
		in.size = 0;
		in.ignor = 0;

		word newWord;
		newWord.begin = 0;

		int position = 0;
		bool isString = false;

		unsigned char symbol;
		char buf;
		while (true)
		{

			input.get(buf);
			if (input.eof())
			{
				in.lines++;
				break;
			}
			symbol = (unsigned char)buf;

			switch (in.code[symbol])
			{
			case IN::F:
					throw ERROR_THROW_IN(111, in.lines, position);
				break;
			case IN::I:
					if (!isString)
					{
						AddWord(in, newWord, position);
						in.size++;
						in.ignor++;
					}
					else newWord.value.push_back(symbol);
				break;
			case IN::E:
					in.lines++;
					position = 0;
					continue;
				break;
			case IN::K:
					if (isString)
					{
						newWord.value.push_back(symbol);
						AddWord(in, newWord, position);
						isString = false;
					}
					else
					{
						AddWord(in, newWord, position, true);
						newWord.value.push_back(symbol);
						isString = true;
					}

					in.size++;
				break;
			case IN::S:
					if (!isString)
					{
						AddWord(in, newWord, position, true);
						in.size++;
						newWord.value.push_back(symbol);
						AddWord(in, newWord, newWord.begin);
					}
					else newWord.value.push_back(symbol);
				break;
			case IN::D:
					newWord.value.push_back(symbol);
					in.size++;
				break;
			default:
					newWord.value.push_back(in.code[symbol]);
					in.size++;
				break;
			}
			position++;
		}
		in.size -= in.lines;
		input.close();
		return in;
	}

	void WriteInputTextInConsole(IN in)
	{
		for (auto i : in.text)
		{
			for (auto c : i.value)std::cout << c;
			std::cout << LEXEMA_DELEMITOR;
		}
	}

	void AddWord(IN& in, word& wd, int pos, bool isOper)
	{
		if (wd.value.size() != 0)
		{
			wd.end = pos;
			wd.line = in.lines;
			in.text.push_back(wd);
			wd.value.clear();
		}
		
		if (!isOper)wd.begin = pos + 1;
		else wd.begin = pos;
	}
};