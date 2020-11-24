#pragma once

#include "includelib.h"
#include "Lex.h"
#include <map>

#define NONE_OPERATOR 0xfff;


namespace PBN
{
	struct PBN
	{
		LT::Entry result[LT_MAXSIZE];
		int size;
		std::map<char, int>  operators = { {'(', 0 }, {')',0} ,{',', 1} , {'>', 2}, {'<', 2},
			{'!', 2}, {'=', 2},{'+', 2}, {'-', 2}, {'*', 3}, {'/', 3} };
	};

	int SearchExpressionPos(int startPos, const LT::LexTable& lt);
	PBN* CreatePN(int pos, LEX::LEX& lex);
	bool BuildCodeInPN(LEX::LEX& lex);
};