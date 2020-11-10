#include "IT.h"

namespace IT
{
	IdTable Create(int size)
	{
		IdTable* it = new IdTable;
		if (size > TI_MAXSIZE)throw ERROR_THROW(120);
		it->maxsize = size;
		it->size = 0;
		it->table = new Entry[TI_MAXSIZE];
		return *it; 
	}

	void Add(IdTable& idtable, Entry entry)
	{
		if (idtable.size == idtable.maxsize)throw ERROR_THROW(121);
		idtable.table[idtable.size] = entry;
		idtable.size++;
	}

	Entry GetEntry(IdTable& idtable, int n)
	{
		if (n >= idtable.size)throw ERROR_THROW(122);
		return idtable.table[n];
	}

	int IsId(IdTable& idtable, Entry ent)
	{
		if (ent.idtype != IT::L)
		{
			for (int i = 0; i < idtable.size; ++i)
			{
				//
				if (strcmp(idtable.table[i].id, ent.id) == 0 && strcmp(idtable.table[i].visibilityRegion, ent.visibilityRegion) == 0)return i;
			}

			if (ent.idtype == IT::N)
			{
				for (int i = 0; i < idtable.size; i++)
				{
					if (strcmp(idtable.table[i].id, ent.id) == 0 && idtable.table[i].visibilityRegion[0] == '$' &&
						idtable.table[i].idtype == IT::F)return i;
				}
			}
		}
		else
		{
			for (int i = 0; i < idtable.size; ++i)
			{
				switch (ent.iddatatype)
				{
				case IT::INT:
					if (ent.idtype == idtable.table[i].idtype && ent.value.vint == idtable.table[i].value.vint)return i;
					break;
				case IT::STR:
					if (ent.idtype == idtable.table[i].idtype && strcmp((char*)idtable.table[i].value.vstr.str, (char*)ent.value.vstr.str) == 0)
						return i;
					break;
				default:
					break;
				}
			}
		}

		return TI_NULLIDX;
	}

	void Delete(IdTable& idtable)
	{
		delete[] &idtable;
	}
}