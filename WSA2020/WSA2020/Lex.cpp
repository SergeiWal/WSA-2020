#include "Lex.h"

namespace LEX
{
	LexExample::LexExample(char firstCh, FST::FST nfst, LexType tp)
	{
		firstSymbol = firstCh;
		fst = nfst;
		type = tp;
	}

	unsigned char* UchVectorToString(std::vector<unsigned char> word)
	{
		unsigned char* str = new unsigned char[word.size()];
		for (int i = 0; i < word.size(); ++i)str[i] = word[i];
		return str;
	}


	LexType LAnaliz( In::word word)
	{
		LexExample tokensArray[TOKENS_ARRAY_SIZE] = TOKENS_ARRAY;

		unsigned char* str = UchVectorToString(word.value);
		str[word.value.size()] = '\0';

		for (int i = 0; i < TOKENS_ARRAY_SIZE; ++i)
		{
			if (word.value[0] == tokensArray[i].firstSymbol)
			{
				tokensArray[i].fst.string = str;
				if (FST::execute(tokensArray[i].fst))
				{
					return tokensArray[i].type;
				}
				
			}
		}

		FST::FST o_fst
		{
			str,
			OPERATION
		};
		if (FST::execute(o_fst))return LexType::O;

		FST::FST id_fst
		{
			str,
			ID
		};
		if (FST::execute(id_fst))return LexType::I;

		throw ERROR_THROW_IN(123, word.line, word.begin);
	}
	
}