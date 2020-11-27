#include "CG.h"

namespace CG
{
	std::ofstream* CreateAsmFile()
	{
		std::ofstream* stream = new std::ofstream;
		stream->open(FILENAME);
		if (!stream->is_open())throw ERROR_THROW(124);
		*stream << PROC_SERIES << ENDL << MODEL << ENDL << KERNEL_LIB
			<< ENDL << EXIT_PROC << ENDL << STACK;
		return stream;
	}

	void ConstBlockFill(std::ofstream* file, IT::IdTable it)
	{
		*file << STACK << ENDL;
		for (int i = 0; i < it.size; ++i)
		{
			if (it.table[i].idtype == IT::IDTYPE::L && it.table[i].id != NULL)
			{
				*file << it.table[i].id << SPACE;
				switch (it.table[i].iddatatype)
				{
				case IT::IDDATATYPE::BL:
					*file << BYTE << SPACE;
					if (it.table[i].value.vbool)*file << TRUE;
					else *file << FALSE;
					break;
				case IT::IDDATATYPE::INT:
					*file << WORD_TYPE << SPACE
						<< it.table[i].value.vint;
					break;
				case IT::IDDATATYPE::STR:
					*file << BYTE << SPACE << '\"' << it.table[i].value.vstr.str << "\"" << LEX_COMA << 0;
					break;
				default:
					break;
				}
				*file << ENDL << ENDL;
			}
		}
	}

	void DataBLockFILL(std::ofstream* file, IT::IdTable it)
	{

	}

	void CloseFile(std::ofstream* file)
	{
		file->close();
		delete[] file;
	}
};

