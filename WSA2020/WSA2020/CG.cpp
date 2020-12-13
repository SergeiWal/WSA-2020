#include "CG.h"

namespace CG
{
	std::ofstream* CreateAsmFile()
	{
		std::ofstream* stream = new std::ofstream;
		stream->open(FILENAME);
		if (!stream->is_open())throw ERROR_THROW(124);
		*stream << PROC_SERIES << ENDL << MODEL << ENDL << LIBRARY
			<< ENDL << EXIT_PROC << ENDL << STLIB_FUNC << ENDL;

		return stream;
	}


	void ExtrnFuncAdd(std::ofstream* file, IT::IdTable it, LT::LexTable lt)
	{
		for (int i = 0;i<lt.size && lt.table[i].lexema[0] != LEX_MAIN;++i)
		{
			if (lt.table[i].lexema[0] == LEX_EXTR)
			{
				i += 2;
				*file << "EXTRN " << it.table[lt.table[i].idxTI].id << " :proc" << ENDL;
			}
		}
	}


	void ConstBlockFill(std::ofstream* file, IT::IdTable it)
	{
		*file << STACK << ENDL << CONST << ENDL;
		for (int i = 0; i < it.size; ++i)
		{
			if (it.table[i].idtype == IT::IDTYPE::L && it.table[i].id != NULL)
			{
				*file << it.table[i].visibilityRegion << '_' << it.table[i].id << SPACE;
				switch (it.table[i].iddatatype)
				{
				case IT::IDDATATYPE::BL:
					*file << WORD << SPACE;
					if (it.table[i].value.vbool)*file << TRUE;
					else *file << FALSE;
					break;
				case IT::IDDATATYPE::INT:
					*file << SHORT << SPACE
						<< it.table[i].value.vint;
					break;
				case IT::IDDATATYPE::STR:
					*file << BYTE << SPACE << '\"' << it.table[i].value.vstr.str << '\"' << LEX_COMA << 0;
					break;
				default:
					break;
				}
				*file << ENDL << ENDL;
			}
		}
	}

	void SetDataValue(std::ofstream* file, IT::IdTable it, int pos)
	{
		switch (it.table[pos].iddatatype)
		{
		case IT::IDDATATYPE::BL:
			*file << WORD << SPACE;
			if (it.table[pos].value.vbool)*file << TRUE;
			else *file << FALSE;
			break;
		case IT::IDDATATYPE::INT:
			*file << SHORT << SPACE
				<< it.table[pos].value.vint;
			break;
		case IT::IDDATATYPE::STR:
			*file << SPACE << SPACE << BYTE << SPACE << TI_STR_MAXSIZE  << SPACE << "dup (\"0\"), 0";//!
			break;
		default:
			break;
		}
	}

	void DataBLockFILL(std::ofstream* file, IT::IdTable it)
	{
		*file << DATA << ENDL;
		for (int i = 0; i < it.size; ++i)
		{
			switch (it.table[i].idtype)
			{
			case IT::IDTYPE::V:

				*file << ";------variable-------------" << it.table[i].id << "--------------variable--------" << ENDL;
				*file << it.table[i].visibilityRegion << '_' << it.table[i].id << SPACE;
				SetDataValue(file, it, i);
				*file << ENDL;
				break;
			case IT::IDTYPE::F:
				*file << ";-------------------" << it.table[i].id << " return value -----------------" << ENDL;
				*file << RET << it.table[i].id << SPACE;
				SetDataValue(file, it, i);
				*file << ENDL;
				break;
			case IT::IDTYPE::A:
				*file << ";-------------------" << it.table[i].visibilityRegion << " parameters data -----------------" << ENDL;
				if (it.table[i].visibilityRegion == MAIN_VISIBLE)*file << it.table[i].id << SPACE;
				else *file <<
					it.table[i].visibilityRegion << '_' << it.table[i].id << SPACE;
				SetDataValue(file, it, i);
				*file << ENDL;
				break;
			default:
				break;
			}
		}
	}

	void generationOperation(std::ofstream* file, char opr, IT::IDDATATYPE type, int number, bool isBinary)
	{
		switch (opr)
		{
		case '+':
			if (type == IT::IDDATATYPE::INT)*file << "pop bx" << ENDL << "pop ax" << ENDL
				<< "add ax,bx" << ENDL << "push ax" << ENDL;
			else if (type == IT::IDDATATYPE::STR)*file << "call concat" << ENDL
				<< "push eax" << ENDL << "push 256" << ENDL;
			break;
		case '-':
			if (isBinary)*file << "pop bx" << ENDL << "pop ax" << ENDL
				<< "sub ax,bx" << ENDL << "push ax" << ENDL;
			else *file << "pop ax" << ENDL << "neg ax" << ENDL;
			break;
		case '*':
			*file << "pop bx" << ENDL << "pop ax" << ENDL
				<< "imul bx" << ENDL << "push ax" << ENDL;
			break;
		case '/':
			*file << "pop bx" << ENDL << "pop ax" << ENDL
				<< "mov dx,0" << ENDL
				<< "idiv bx" << ENDL << "push ax" << ENDL;
			break;
		case '%':
			*file << "pop bx" << ENDL << "pop ax" << ENDL
				<< "mov dx,0" << ENDL
				<< "idiv bx" << ENDL << "push dx" << ENDL;
			break;
		case '<':
			if (type == IT::IDDATATYPE::STR)*file << "call stringEquel" << ENDL
				<< "push eax" << ENDL << "cmp eax,1" << ENDL << "jnz " << "true_" << number << ENDL
				<< "push 0" << ENDL << "jmp " << "end_" << number << ENDL
				<< "true_" << number << ": " << ENDL << "\t push 1" << ENDL
				<< "end_" << number << ": " << ENDL;
			else *file << "pop bx" << ENDL << "pop ax" << ENDL
				<< "cmp ax,bx" << ENDL << "js " << "true_" << number << ENDL
				<< "push 0" << ENDL << "jmp " << "end_" << number << ENDL
				<< "true_" << number << ": " << ENDL << "\t push 1" << ENDL
				<< "end_" << number << ": " << ENDL;
			break;
		case '>':
			if (type == IT::IDDATATYPE::STR)*file << "call stringEquel" << ENDL
				<< "push eax" << ENDL << "cmp eax,1" << ENDL << "jz " << "true_" << number << ENDL
				<< "push 0" << ENDL << "jmp " << "end_" << number << ENDL
				<< "true_" << number << ": " << ENDL << "\t push 1" << ENDL
				<< "end_" << number << ": " << ENDL;
			else *file << "pop bx" << ENDL << "pop ax" << ENDL
				<< "cmp ax,bx" << ENDL << "jns " << "true_" << number << ENDL
				<< "push 0" << ENDL << "jmp " << "end_" << number << ENDL
				<< "true_" << number << ": " << ENDL << "\t push 1" << ENDL
				<< "end_" << number << ": " << ENDL;
			break;
		case '=':
			if (type == IT::IDDATATYPE::STR)*file << "call stringEquel" << ENDL
				<< "push eax" << ENDL << "cmp eax,0" << ENDL << "jz " << "true_" << number << ENDL
				<< "push 0" << ENDL << "jmp " << "end_" << number << ENDL
				<< "true_" << number << ": " << ENDL << "\t push 1" << ENDL
				<< "end_" << number << ": " << ENDL;
			else *file << "pop bx" << ENDL << "pop ax" << ENDL
				<< "cmp eax,ebx" << ENDL << "jz " << "true_" << number << ENDL
				<< "push 0" << ENDL << "jmp " << "end_" << number << ENDL
				<< "true_" << number << ": " << ENDL << "\t push 1" << ENDL
				<< "end_" << number << ": " << ENDL;
			break;
		case '!':
			if (type == IT::IDDATATYPE::STR)*file << "call stringEquel" << ENDL
				<< "push eax" << ENDL << "cmp eax,1" << ENDL << "jnz " << "true_" << number << ENDL
				<< "push 0" << ENDL << "jmp " << "end_" << number << ENDL
				<< "true_" << number << ": " << ENDL << "\t push 1" << ENDL
				<< "end_" << number << ": " << ENDL;
			else *file << "pop bx" << ENDL << "pop ax" << ENDL
				<< "cmp ax,bx" << ENDL << "jnz " << "true_" << number << ENDL
				<< "push 0" << ENDL << "jmp " << "end_" << number << ENDL
				<< "true_" << number << ": " << ENDL << "\t push 1" << ENDL
				<< "end_" << number << ": " << ENDL;
			break;
		default:
			break;
		}
	}

	CG::Parametr::Parametr(std::string nm, IT::IDDATATYPE tp)
	{
		name = nm;
		type = tp;
	}

	void CodeBlockFILL(std::ofstream* file, IT::IdTable it, LT::LexTable lt)
	{
		bool isMain = false;
		bool isCycle = false;
		bool isWrite = false;
		bool isReturn = false;
		bool isExpr = false;
		bool isBinary = true;
		bool isExtrn = false;
		int resultBufferIdx = -1;		//индекс переменной назначения, если -1 то не активен
		int parameterCount;				//кол-во параметров вызова функции
		int idxBuf;						//буфер индекса
		std::string currentCycleName;   //имя цикла - используется для создания меток
		std::string funcName;			//имя текущей функции		
		IT::IDDATATYPE currentType = IT::IDDATATYPE::NONE;			//тип данных  последнего идентификатора
		std::map<std::string, std::vector<Parametr>> parametrs;

		*file << CODE_BLOCK << ENDL;

		for (int i = 0;i<lt.size;++i)
		{
			switch (lt.table[i].lexema[0])
			{
			case LEX_ID:
				currentType = it.table[lt.table[i].idxTI].iddatatype;
				if (lt.table[i + 1].lexema[0] == LEX_EQUALL)
				{
					resultBufferIdx = i;
					i++;
				}
				else if (currentType != IT::IDDATATYPE::STR)
				{
					*file << "push " << it.table[lt.table[i].idxTI].visibilityRegion
						<< '_' << it.table[lt.table[i].idxTI].id << ENDL;
				}
				else
				{
					*file << "push offset " << it.table[lt.table[i].idxTI].visibilityRegion
						<< '_' << it.table[lt.table[i].idxTI].id << ENDL
						<< "push lengthof " <<  it.table[lt.table[i].idxTI].visibilityRegion
						<< '_' << it.table[lt.table[i].idxTI].id << ENDL;
				}
				break;
			case LEX_LITERAL:
				currentType = it.table[lt.table[i].idxTI].iddatatype;
				if (currentType != IT::IDDATATYPE::STR)
				{
					*file << "push " << it.table[lt.table[i].idxTI].visibilityRegion
						<< '_' << it.table[lt.table[i].idxTI].id << ENDL;
				}
				else
				{
					*file << "push offset " << it.table[lt.table[i].idxTI].visibilityRegion
						<< '_' << it.table[lt.table[i].idxTI].id << ENDL
						<< "push lengthof " << it.table[lt.table[i].idxTI].visibilityRegion
						<< '_' << it.table[lt.table[i].idxTI].id << ENDL;
				}
				break;
			case LEX_CALL:
				idxBuf = ++i;
				if (it.table[lt.table[idxBuf].idxTI].idtype == IT::IDTYPE::E)isExtrn = true;
				while (lt.table[i].lexema[0] != SEQ)i++;
				parameterCount = it.table[lt.table[i].idxTI].value.vint;
				//проверка на колво
				if (parameterCount != parametrs[it.table[lt.table[idxBuf].idxTI].id].size())throw ERROR_THROW_IN(132, lt.table[idxBuf].sn, 0);
				for (int j = parameterCount, k =0; j > 0; --j, k++)
				{ 
					--i;
					//проверка на совпадение типов
					if (it.table[lt.table[i].idxTI].iddatatype != parametrs[it.table[lt.table[idxBuf].idxTI].id][k].type)
						throw ERROR_THROW_IN(133, lt.table[idxBuf].sn, 0);
					if (it.table[lt.table[i].idxTI].iddatatype != IT::IDDATATYPE::STR)
					{
						*file << "mov ax," << it.table[lt.table[i].idxTI].visibilityRegion
							<< '_' << it.table[lt.table[i].idxTI].id << ENDL
							<< "mov " << parametrs[it.table[lt.table[idxBuf].idxTI].id][k].name << ",ax" << ENDL;
					}
					else
					{
						*file << "cld" << ENDL << "mov ecx, lengthof " << it.table[lt.table[i].idxTI].visibilityRegion
							<< '_' << it.table[lt.table[i].idxTI].id << ENDL
							<< "lea edi," << parametrs[it.table[lt.table[idxBuf].idxTI].id][k].name << ENDL
							<< "lea esi," << it.table[lt.table[i].idxTI].visibilityRegion
							<< '_' << it.table[lt.table[i].idxTI].id << ENDL << "rep movsb" << ENDL;
					}
				}
				if (isExtrn)
				{
					for (auto c : parametrs[it.table[lt.table[idxBuf].idxTI].id])
					{
						if (c.type != IT::IDDATATYPE::STR)
						{
							*file << "push " << c.name << ENDL;
						}
						else
						{
							*file << "push offset " << c.name << ENDL
								<< "push lengthof " << c.name << ENDL;
						}
					}
				}
				--i;
				*file << "call " << it.table[lt.table[i].idxTI].id << ENDL;
				if (it.table[lt.table[i].idxTI].idtype == IT::IDTYPE::E && (resultBufferIdx != -1 || isExpr || isWrite))
				{
					switch (it.table[lt.table[i].idxTI].iddatatype)
					{
					case IT::IDDATATYPE::BL:
						currentType = IT::IDDATATYPE::BL;
						*file << "push eax" << ENDL;
						break;
					case IT::IDDATATYPE::INT:
						currentType = IT::IDDATATYPE::INT;
						*file << "push eax" << ENDL;
						break;
					case IT::IDDATATYPE::STR:
						currentType = IT::IDDATATYPE::STR;
						*file << "push offset eax" << ENDL << "push lengthof eax" << ENDL;
						break;
					default:
						break;
					}
				}

				if (it.table[lt.table[i].idxTI].idtype == IT::IDTYPE::F && (resultBufferIdx!=-1 || isExpr || isWrite))
				{
					switch (it.table[lt.table[i].idxTI].iddatatype)
					{
					case IT::IDDATATYPE::BL:
						currentType = IT::IDDATATYPE::BL;
						*file << "push " << RET << it.table[lt.table[i].idxTI].id << ENDL;
						break;
					case IT::IDDATATYPE::INT:
						currentType = IT::IDDATATYPE::INT;
						*file << "push " << RET << it.table[lt.table[i].idxTI].id << ENDL;
						break;
					case IT::IDDATATYPE::STR:
						currentType = IT::IDDATATYPE::STR;
						*file << "push offset " << RET << it.table[lt.table[i].idxTI].id << ENDL;
						*file << "push lengthof " << RET << it.table[lt.table[i].idxTI].id << ENDL;
						break;
					default:
						break;
					}
				}
				i += parameterCount + 1;
				isExtrn = false;
				break;
			case LEX_OPERATION:
				isExpr = true;
				if (lt.table[i - 2].lexema[0] == LEX_EQUALL)isBinary = false;
				generationOperation(file, it.table[lt.table[i].idxTI].id[0], currentType, i, isBinary);
				isBinary = true;
				break;
			case LEX_EXTR:
				i+=2;
				funcName = it.table[lt.table[i].idxTI].id;
				while (lt.table[i].lexema[0] != LEX_RIGHTHESIS)
				{
					++i;
					if (lt.table[i].lexema[0] == LEX_ID)
						parametrs[funcName].push_back(Parametr(funcName + '_' + it.table[lt.table[i].idxTI].id, it.table[lt.table[i].idxTI].iddatatype));
				}
				break;
			case LEX_FUNCTION:
				i++;
			case LEX_PROC:
				i++;
				*file << (funcName = it.table[lt.table[i].idxTI].id) << " PROC " << SAVE_REGISTRS << ENDL << SAVE_BASE << ENDL;
				while (lt.table[i].lexema[0] != LEX_RIGHTHESIS)++i;
				parameterCount = i;//немного не по назначению
				while (lt.table[i].lexema[0] != LEX_LEFTHESIS)
				{
					if (lt.table[i].lexema[0] == LEX_ID)
						parametrs[funcName].push_back(Parametr(funcName + '_' + it.table[lt.table[i].idxTI].id, it.table[lt.table[i].idxTI].iddatatype));
					--i;
				}
				i = parameterCount;
				break;
			case LEX_RETURN:
				isReturn = true;
				break;
			case LEX_SEMICOLON:
				if (resultBufferIdx != -1)
				{
					if (currentType != IT::IDDATATYPE::STR)
						*file << "pop " << it.table[lt.table[resultBufferIdx].idxTI].visibilityRegion
						<< '_' << it.table[lt.table[resultBufferIdx].idxTI].id << ENDL;
					else *file << "cld\npop ecx\npop esi\nlea edi, " << it.table[lt.table[resultBufferIdx].idxTI].visibilityRegion
						<< '_' << it.table[lt.table[resultBufferIdx].idxTI].id << ENDL
						<< "rep movsb" << ENDL;
					resultBufferIdx = -1;
				}
				else if (isReturn)
				{
					if (currentType != IT::IDDATATYPE::STR)
						*file << "pop ax" << ENDL << "mov " << RET << funcName << LEX_COMA << "ax" << ENDL;
					else *file << "cld\npop ecx\npop esi\nlea edi, " << RET << funcName << ENDL
						<< "rep movsb" << ENDL ;

					isReturn = false;
				}
				else if (isWrite)
				{
					switch (currentType)
					{
					case IT::IDDATATYPE::INT:
						*file << "call writeNumberBin" << ENDL;
						break;
					case IT::IDDATATYPE::BL:
						*file  << "call writeBool" << ENDL;
						break;
					case IT::IDDATATYPE::STR:
						*file << "call writeStr" << ENDL ;
						break;
					default:
						break;
					}

					isWrite = false;
				}
				isExpr = false;
				break;
			case LEX_MAIN:
				*file << "WSA2020 PROC " << SAVE_REGISTRS << ENDL << SAVE_BASE << ENDL << W1251_SET << ENDL;
				funcName = "WSA2020";
				isMain = true;
				break;
			case LEX_LEFTBRACE:
				if (isCycle)
				{
					*file << "pop eax" << ENDL
						<< "cmp eax,1" << ENDL << "jz " << currentCycleName << "_BEGIN" << ENDL
						<< "jnz " << currentCycleName << "_END" << ENDL
						<< currentCycleName << "_BEGIN: " << ENDL;
				}
				break;
			case LEX_BRACELET:
				if (!isCycle)
				{
					if (isMain)isMain = false;
					*file << BASE_RECOVERY << ENDL << "ret" << ENDL << funcName << " ENDP" << ENDL;
				}
				else
				{
					*file << "jmp " << currentCycleName << ENDL
						<< currentCycleName << "_END: " << ENDL;
					isCycle = false;
				}
				break;
			case LEX_CYCLE:
				isCycle = true;
				currentCycleName = "CYCLE_" + std::to_string(i);
				*file << currentCycleName << ": " << ENDL;
				break;
			case LEX_VAR:
				i += 2;
				break;
			case LEX_WRITE:
				isWrite = true;
				break;
			default:
				break;
			}
		}
	}

	void asmMain(std::ofstream* file)
	{
		*file << "main PROC" << ENDL << ENDL << "call WSA2020" << ENDL
			<< "push eax" << ENDL << "call ExitProcess" << ENDL
			<< "main ENDP" << ENDL << "end main";
	}

	void CloseFile(std::ofstream* file)
	{
		file->close();
		delete[] file;
	}
};

