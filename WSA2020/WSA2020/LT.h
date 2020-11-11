#pragma once

#include "includelib.h"
#include "Error.h"

#define LEXEMA_FIXSIZE 1 
#define LT_MAXSIZE 4096
#define LT_IT_NULLIDX 0xffffffff
#define LEX_TYPE 't'
#define LEX_ID 'i'
#define LEX_LITERAL 'l'
#define LEX_FUNCTION 'f'
#define LEX_PROC 'p'
#define LEX_VAR 'v'
#define LEX_RETURN 'r'
#define LEX_WRITE 'w'
#define LEX_CYCLE 'c'
#define LEX_MAIN 'm'
#define LEX_OPERATION 'o'
#define LEX_LESS '<'
#define LEX_MORE '>'
#define LEX_SEMICOLON ';'
#define LEX_COMA ','
#define LEX_LEFTBRACE '{'
#define LEX_BRACELET '}'
#define LEX_LEFTHESIS '('
#define LEX_RIGHTHESIS ')'
#define LEX_CALL '$'
#define LEX_EQUALL '='

namespace LT
{
	struct Entry
	{
		int sn;
		int idxTI; 
		char lexema[LEXEMA_FIXSIZE];
	};

	struct LexTable
	{
		int maxsize;
		int size;
		Entry* table;
	};

	LexTable Create(int size);
	void Add(LexTable& lextable, Entry entry);
	Entry GetAntry(LexTable& lextable, int n);
	void Delete(LexTable& lextable);
}