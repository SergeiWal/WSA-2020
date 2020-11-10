#pragma once

#include "includelib.h"
#include "Error.h"

#define ID_MAXSIZE 5
#define TI_MAXSIZE 4096
#define TI_INT_DEFAULT 0x00000000
#define TI_STR_DEFAULT 0x00
#define TI_NULLIDX 0xffffffff
#define TI_STR_MAXSIZE 255

namespace IT
{
	enum IDDATATYPE { INT = 1, STR = 2 , NLL = 3};
	enum IDTYPE { V = 1, F = 2, P = 3, L = 5 , N = 4};


	struct Entry
	{
		int idxfirstLE;
		char id[ID_MAXSIZE];
		IDDATATYPE iddatatype;
		IDTYPE idtype;
		char visibilityRegion[ID_MAXSIZE];
		union 
		{
			int vint;
			struct
			{
				char len;
				unsigned char str[TI_STR_MAXSIZE - 1];

			} vstr;
		}value;
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