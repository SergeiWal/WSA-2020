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
	void SetNewLtNodeValue(LT::Entry& entry, char value)
	{
		entry.lexema[0] = value;
		entry.lexema[1] = STR_END;
	}

	LexType LAnaliz( In::word word)
	{
		LexExample tokensArray[TOKENS_ARRAY_SIZE] = TOKENS_ARRAY;

		unsigned char* str = UchVectorToString(word.value);
		str[word.value.size()] = STR_END;

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

	void TableFilling(In::IN in, LEX& lex)
	{
		LexType lextype;
		
		for (int i = 0; i<in.text.size(); ++i)
		{
			LT::Entry* newEntry = new LT::Entry;
			newEntry->sn = in.text[i].line;
			newEntry->idxTI = LT_IT_NULLIDX;

			if (in.text[i].value.size() == 1 && lex.one_symbol_lexems.find(in.text[i].value[0]) != lex.one_symbol_lexems.end())
			{
				SetNewLtNodeValue(*newEntry, in.text[i].value[0]);
			}
			else
			{
				lextype = LAnaliz(in.text[i]);
				switch (lextype)
				{
				case LexType::F:
					SetNewLtNodeValue(*newEntry, LEX_FUNCTION);
					break;
				case LexType::I:
					SetNewLtNodeValue(*newEntry, LEX_ID);
					break;
				case LexType::L:
					SetNewLtNodeValue(*newEntry, LEX_LITERAL);
					break;
				case LexType::M:
					SetNewLtNodeValue(*newEntry, LEX_MAIN);
					break;
				case LexType::O:
					SetNewLtNodeValue(*newEntry, LEX_OPERATION);
					break;
				case LexType::P:
					SetNewLtNodeValue(*newEntry, LEX_PROC);
					break;
				case LexType::R:
					SetNewLtNodeValue(*newEntry, LEX_RETURN);
					break;
				case LexType::T:
					SetNewLtNodeValue(*newEntry, LEX_TYPE);
					break;
				case LexType::V:
					SetNewLtNodeValue(*newEntry, LEX_VAR);
					break;
				case LexType::C:
					SetNewLtNodeValue(*newEntry, LEX_CYCLE);
					break;
				case LexType::W:
					SetNewLtNodeValue(*newEntry, LEX_WRITE);
					break;
				default:
					break;
				}

			}
			LT::Add(lex.lextable, *newEntry);
		}
	}

	void LexTableOut(LT::LexTable lt)
	{
		std::ofstream out;
		out.open("LexTable.txt");
		if (!out.is_open())throw ERROR_THROW(123);
		int line = 0;
		out << "0000 ";
		for (int i = 0; i < lt.size; ++i)
		{
			if (lt.table[i].sn > line)
			{
				out << "\n";
				line = lt.table[i].sn;
				if (line < 10)out << "000";
				if (line < 100 && line >= 10)out << "00";
				if (line >= 100 && line < 1000)out << "0";
				out << line << " ";
			}
			out << lt.table[i].lexema;
		}
		out.close();
	}
}