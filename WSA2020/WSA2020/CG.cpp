#include "CG.h"

namespace CG
{
	std::ofstream* CreateAsmFile()
	{
		std::ofstream* stream = new std::ofstream;
		stream->open(FILENAME);
		if (!stream->is_open())throw ERROR_THROW(124);
		*stream << ASM_HEADER << STLIB_FUNC << std::endl;
		return stream;
	}


	void ExtrnFuncAdd(std::ofstream* file, IT::IdTable it, LT::LexTable lt)
	{
		for (int i = 0;i<lt.size && lt.table[i].lexema[0] != LEX_MAIN;++i)
		{
			if (lt.table[i].lexema[0] == LEX_EXTR)
			{
				i += 2; 
				*file << EXTRN_FUNC_CONNECT(it.table[lt.table[i].idxTI].id);
			}
		}
	}


	void ConstBlockFill(std::ofstream* file, IT::IdTable it)
	{
		*file << STACK << CONST ;
		*file << OWERFLOW_MESSAGE << ENDL;
		*file << ZERODIV_MESSAGE << ENDL;
		for (int i = 0; i < it.size; ++i)
		{
			if (it.table[i].idtype == IT::IDTYPE::L && it.table[i].id != NULL)
			{
				*file << GET_ID(it.table[i].visibilityRegion, it.table[i].id);
				switch (it.table[i].iddatatype)
				{
				case IT::IDDATATYPE::BL:
					if (it.table[i].value.vbool)*file << GET_TYPE_VALUE(WORD, TRUE);
					else *file << GET_TYPE_VALUE(WORD, FALSE);
					break;
				case IT::IDDATATYPE::INT:
					*file << GET_TYPE_VALUE(SHORT, it.table[i].value.vint);
					break;
				case IT::IDDATATYPE::STR:
					*file << GET_TYPE_VALUE_STR(it.table[i].value.vstr.str);
					break;
				case IT::IDDATATYPE::CHR:
					*file << GET_TYPE_VALUE_STR(it.table[i].value.vchar);
					break;
				default:
					break;
				}
				*file << std::endl << std::endl;
			}
		}
	}

	void SetDataValue(std::ofstream* file, IT::IdTable it, int pos)
	{
		switch (it.table[pos].iddatatype)
		{
		case IT::IDDATATYPE::BL:
			if (it.table[pos].value.vbool)*file << GET_TYPE_VALUE(WORD, TRUE);
			else *file << GET_TYPE_VALUE(WORD, TRUE);
			break;
		case IT::IDDATATYPE::INT:
			*file << GET_TYPE_VALUE(SHORT, it.table[pos].value.vint);
			break;
		case IT::IDDATATYPE::STR:
			*file << DEFAULT_STR_INIT;//!
			break;
		case IT::IDDATATYPE::CHR:
			*file << DEFAULT_CHAR_INIT;
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
				*file << GET_ID(it.table[i].visibilityRegion, it.table[i].id);
				SetDataValue(file, it, i);
				*file << std::endl;
				break;
			case IT::IDTYPE::F:
				*file << ";-------------------" << it.table[i].id << " return value -----------------" << ENDL;
				*file << GET_RET_VARIABLE(it.table[i].id);
				SetDataValue(file, it, i);
				*file << std::endl;
				break;
			case IT::IDTYPE::A:
				*file << ";-------------------" << it.table[i].visibilityRegion << " parameters data -----------------" << ENDL;
				if (it.table[i].visibilityRegion == MAIN_VISIBLE)*file << it.table[i].id << SPACE;
				else *file << GET_ID(it.table[i].visibilityRegion, it.table[i].id);
				SetDataValue(file, it, i);
				*file << std::endl;
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
			if (type == IT::IDDATATYPE::INT)*file << EXPR_INT_PLUS;
			else if (type == IT::IDDATATYPE::STR)*file << EXPR_STR_CONCAT;
			break;
		case '-':
			if (isBinary)*file << EXPR_INT_DIFF;
			else *file << EXPR_INT_NEG;
			break;
		case '*':
			*file << EXPR_MUL;
			break;
		case '/':
			*file << EXPR_DIV;
			break;
		case '%':
			*file << EXPR_MOD;
			break;
		case '<':
			if (type == IT::IDDATATYPE::STR)*file << EXPR_STR_LESS(number);
			else *file << EXPR_INT_LESS(number);
			break;
		case '>':
			if (type == IT::IDDATATYPE::STR)*file << EXPR_STR_MORE(number);
			else *file << EXPR_INT_MORE(number);
			break;
		case '=':
			if (type == IT::IDDATATYPE::STR)*file << EXPR_STR_EQUEL(number);
			else *file << EXPR_INT_EQUEL(number);
			break;
		case '!':
			if (type == IT::IDDATATYPE::STR)*file << EXPR_STR_NOT_EQUEL(number);
			else *file << EXPR_INT_NOT_EQUEL(number);
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
				else if (currentType != IT::IDDATATYPE::STR && currentType != IT::IDDATATYPE::CHR)
					*file << PUSH(it.table[lt.table[i].idxTI].visibilityRegion, it.table[lt.table[i].idxTI].id) << std::endl;
				else
					*file << PUSH_STR(it.table[lt.table[i].idxTI].visibilityRegion, it.table[lt.table[i].idxTI].id) << std::endl;
				break;
			case LEX_LITERAL:
				currentType = it.table[lt.table[i].idxTI].iddatatype;
				if (currentType != IT::IDDATATYPE::STR && currentType != IT::IDDATATYPE::CHR)
					*file << PUSH(it.table[lt.table[i].idxTI].visibilityRegion, it.table[lt.table[i].idxTI].id) << std::endl;
				else
					*file << PUSH_STR(it.table[lt.table[i].idxTI].visibilityRegion, it.table[lt.table[i].idxTI].id) << std::endl;
				break;
			case LEX_CALL:
				idxBuf = ++i;
				if (it.table[lt.table[idxBuf].idxTI].idtype == IT::IDTYPE::E)isExtrn = true;
				while (lt.table[i].lexema[0] != SEQ)i++;
				parameterCount = it.table[lt.table[i].idxTI].value.vint;
				
				for (int j = parameterCount, k =0; j > 0; --j, k++)
				{ 
					--i;
					if (it.table[lt.table[i].idxTI].iddatatype != IT::IDDATATYPE::STR && it.table[lt.table[i].idxTI].iddatatype != IT::IDDATATYPE::CHR)
						*file <<
						PARAM_TRANS(it.table[lt.table[i].idxTI].visibilityRegion, it.table[lt.table[i].idxTI].id, parametrs[it.table[lt.table[idxBuf].idxTI].id][k].name)
						<< std::endl;
					else
						*file << PARAM_STR_TRANS(it.table[lt.table[i].idxTI].visibilityRegion, it.table[lt.table[i].idxTI].id, parametrs[it.table[lt.table[idxBuf].idxTI].id][k].name)
						<< std::endl;
				}
				if (isExtrn)
				{
					for (auto c : parametrs[it.table[lt.table[idxBuf].idxTI].id])
					{
						if (c.type != IT::IDDATATYPE::STR && c.type != IT::IDDATATYPE::CHR)
							*file << EXTR_PARAM(c.name) << std::endl;
						else
							*file << EXTR_PARAM_STR(c.name) << std::endl;
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
						*file << EXTR_RET;
						break;
					case IT::IDDATATYPE::INT:
						currentType = IT::IDDATATYPE::INT;
						*file << EXTR_RET;
						break;
					case IT::IDDATATYPE::CHR:
						currentType = IT::IDDATATYPE::CHR;
						*file << EXTR_RET_STR;
						break;
					case IT::IDDATATYPE::STR:
						currentType = IT::IDDATATYPE::STR;
						*file << EXTR_RET_STR;
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
						*file << RET_VALUE(it.table[lt.table[i].idxTI].id) << std::endl;
						break;
					case IT::IDDATATYPE::INT:
						currentType = IT::IDDATATYPE::INT;
						*file << RET_VALUE(it.table[lt.table[i].idxTI].id) << std::endl;
						break;
					case IT::IDDATATYPE::CHR:
						currentType = IT::IDDATATYPE::CHR;
						*file << RET_STR(it.table[lt.table[i].idxTI].id);
						break;
					case IT::IDDATATYPE::STR:
						currentType = IT::IDDATATYPE::STR;
						*file << RET_STR(it.table[lt.table[i].idxTI].id);
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
				funcName = it.table[lt.table[i].idxTI].id;
				*file << FUNC_HEADER(funcName) << std::endl;
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
					if (currentType != IT::IDDATATYPE::STR && currentType != IT::IDDATATYPE::CHR)
						*file << POP(it.table[lt.table[resultBufferIdx].idxTI].visibilityRegion, it.table[lt.table[resultBufferIdx].idxTI].id)
						<< std::endl;
					else
						*file << POP_STR(it.table[lt.table[resultBufferIdx].idxTI].visibilityRegion, it.table[lt.table[resultBufferIdx].idxTI].id)
						<< std::endl;
					resultBufferIdx = -1;
				}
				else if (isReturn)
				{
					if (currentType != IT::IDDATATYPE::STR && currentType != IT::IDDATATYPE::CHR)
						*file << FUNC_RET(funcName);
					else *file << FUNC_RET_STR(funcName);

					isReturn = false;
				}
				else if (isWrite)
				{
					switch (currentType)
					{
					case IT::IDDATATYPE::INT:
						*file << WRITE_INT;
						break;
					case IT::IDDATATYPE::BL:
						*file  <<WRITE_BOOL;
						break;
					case IT::IDDATATYPE::STR:
						*file << WRITE_STR;
						break;
					case IT::IDDATATYPE::CHR:
						*file << WRITE_STR;
						break;
					default:
						break;
					}

					isWrite = false;
				}
				isExpr = false;
				break;
			case LEX_MAIN:
				funcName = MAIN_NAME;
				*file << FUNC_HEADER(funcName);
				isMain = true;
				break;
			case LEX_LEFTBRACE:
				if (isCycle)
					*file << CYCLE_HEADER(currentCycleName);
				break;
			case LEX_BRACELET:
				if (!isCycle)
				{
					if (isMain)isMain = false;
					*file << BASE_RECOVERY  << "\nret\n"  << OVERFLOW  << ZERODIV << std::endl << funcName << " ENDP" << std::endl;
				}
				else
				{
					*file << CYCLE_FOOTER(currentCycleName);
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
		*file << ASM_MAIN;
	}


	void CloseFile(std::ofstream* file)
	{
		file->close();
		delete[] file;
	}
};

