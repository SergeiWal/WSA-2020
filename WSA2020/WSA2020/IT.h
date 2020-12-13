#pragma once

#include "Error.h"


#define ID_MAXSIZE 8
#define TI_MAXSIZE 4096
#define TI_INT_DEFAULT 0x00000000
#define TI_STR_DEFAULT 0x00
#define TI_NULLIDX 0xffffffff
#define TI_STR_MAXSIZE 255
#define TI_SHORT_MAXSIZE  32767
#define TI_SHORT_NEG_MAXSIZE -32768
#define GLOBAL_VISIBLE "global"
#define MAIN_VISIBLE "main"
#define CYCLE_VISIBLE(i) "while" + std::to_string(i)
#define SIGN_OCT_NUMBER 'o'
#define SIGN_BIN_NUMBER 'b'
#define LITERAL_NAME "Ltr__"

namespace IT
{
	enum class IDDATATYPE { INT = 1, STR = 2, BL = 3, NONE = 4 };
	enum class IDTYPE { V = 1, F = 2, P = 3, A = 4, L = 5, C = 6, O =7, E =8, NONE = 9 };
	//v- переменная;f-функция;p-процедура;a-параметр функции\процедуры;
	//l- литерал;c - вызов функции\процедуры;none-неопределённое значение;e - подключение внешней функции

	struct Entry
	{
		int idxfirstLE;
		char id[ID_MAXSIZE + 1];
		IDDATATYPE iddatatype;
		IDTYPE idtype;
		std::string visibilityRegion;
		union 
		{
			int vint;
			struct
			{
				int len;
				unsigned char str[TI_STR_MAXSIZE - 1];

			} vstr;
			bool vbool;
		}value;
		Entry() {};
		Entry(IDTYPE nidtype, IDDATATYPE niddatatype, std::string vReg, std::vector<unsigned char> nid);
	};

	struct IdTable
	{
		int maxsize;
		int size;
		Entry* table;
	};



	IdTable Create(int size);
	void Add(IdTable& idtable, Entry entry);
	Entry GetEntry(IdTable& idtable, int n);
	int IsId(IdTable& idtable, Entry ent);
	void Delete(IdTable& idtable);
}