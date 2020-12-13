#pragma once

#include "Error.h"
#include <fstream>


#define IN_MAX_LEN_TEXT 1024*1024
#define IN_CODE_ENDL '\n'
#define LEXEMA_DELEMITOR '|'
#define IN_CODE_TABLE {\
/* 0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  A  |  B  |  C  |  D  |  E  |  F  |    */\
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::I,IN::E,IN::F,IN::F,IN::F,IN::F,IN::F, /*0*/\
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*1*/\
 IN::I,IN::S,IN::K,IN::S,IN::S,IN::S,IN::F,IN::K,IN::S,IN::S,IN::S,IN::S,IN::S,IN::S,IN::F,IN::S, /*2*/\
 IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::F,IN::S,IN::S,IN::S,IN::S,IN::D, /*3*/\
 IN::F,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D, /*4*/\
 IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::F,IN::F,IN::F,IN::F,IN::F, /*5*/\
 IN::F,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D, /*6*/\
 IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::S,IN::F,IN::S,IN::F,IN::F, /*7*/\
     																								   \
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*8*/\
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*9*/\
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*A*/\
 IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F,IN::F, /*B*/\
 IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D, /*C*/\
 IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D, /*D*/\
 IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D, /*E*/\
 IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D,IN::D, /*F*/\
}


namespace In
{
	struct word
	{
		std::vector<unsigned char> value;

		int begin;
		int end;
		int line;
	};

	struct IN
	{
		enum { D = 1024, F = 2048, I = 4096, S = 8192, K = 16384 , E  = 32768};
		int size;
		int lines;
		int ignor;
		std::vector<word> text;
		int code[256] = IN_CODE_TABLE;
	};

	IN getin(wchar_t infile[]);
	void WriteInputTextInConsole(IN in);
	void AddWord(IN& in, word& wd, int pos, bool isOper = false);
};
