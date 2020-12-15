#include "IT.h"

namespace IT
{
	Entry::Entry(IDTYPE nidtype, IDDATATYPE niddatatype, std::string vReg, std::vector<unsigned char> nid)
	{
		
		idtype = nidtype;
		iddatatype = niddatatype;
		visibilityRegion = vReg;
		for (int j = 0; j < nid.size() && j < ID_MAXSIZE; ++j)
		{
			id[j] = nid[j];  
			if ((j + 1) == nid.size() || (j + 1) == ID_MAXSIZE)id[j + 1] = STR_END;
		}
		
	}

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
		std::string visibleForCheck;
		if (ent.idtype == IT::IDTYPE::C)visibleForCheck = GLOBAL_VISIBLE;
		else visibleForCheck = ent.visibilityRegion;

		if (ent.idtype == IT::IDTYPE::L)
		{
			switch (ent.iddatatype)
			{
			case IT::IDDATATYPE::BL:
				for (int i = 0; i < idtable.size; ++i)
					if (idtable.table[i].idtype == IT::IDTYPE::L && idtable.table[i].iddatatype ==IT::IDDATATYPE::BL && 
						idtable.table[i].value.vbool == ent.value.vbool)
						return i;
				break;
			case IT::IDDATATYPE::INT:
				for (int i = 0; i < idtable.size; ++i)
					if (idtable.table[i].idtype == IT::IDTYPE::L && idtable.table[i].value.vint == ent.value.vint)
						return i;
				break;
			case IT::IDDATATYPE::STR:
				for (int i = 0; i < idtable.size; ++i)
					if (idtable.table[i].idtype == IT::IDTYPE::L &&
						strcmp((char*)idtable.table[i].value.vstr.str, (char*)ent.value.vstr.str) == 0)
						return i;
				break;
			default:
				break;
			}
		}
		else
		{
			for (int i = 0; i < idtable.size; ++i)
				if (strcmp(idtable.table[i].id, ent.id) == 0 && idtable.table[i].visibilityRegion == visibleForCheck)
					return i;
		}
				
		return TI_NULLIDX;
	}

	void Delete(IdTable& idtable)
	{
		delete[] &idtable;
	}
}