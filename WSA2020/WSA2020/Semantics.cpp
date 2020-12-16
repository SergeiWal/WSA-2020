#include "Semantics.h"

namespace SA
{
	parametr::parametr(std::string nm, IT::IDDATATYPE tp)
	{
		name = nm;
		type = tp;
	}

	function::function(IT::IDDATATYPE rt, int count, parametr parm ...)
	{
		returnType = rt;
		parametrCount = count;
		parametr* ptr = &parm;
		for (int i = 0; i < count; ++i, ++ptr)parametrs.push_back(*ptr);
	}

	bool SemanticsAnaliz(IT::IdTable idtable, LT::LexTable lextable)
	{
		bool result = false;
		std::string currentName;
		int currentParamIdx = 0;
		IT::IDDATATYPE firstType;
		IT::IDDATATYPE secondType;

		bool isCycle = false; //нахождение в цикле
		bool isCycleOpen = false;
		bool isOpen = false; // открыта ли фигурная скобка
		bool isRet = false; //

		SA sa;
		sa.standartFuncInfo = {SFL_INFO};
		sa.operatorsInfo = {OPR_INFO};

		function* newFunc;
		parametr* newParam;
		
		for (int i = 0; i < lextable.size; ++i)
		{
			switch (lextable.table[i].lexema[0])
			{
			case LEX_FUNCTION:
				i += 2;
				currentName = idtable.table[lextable.table[i].idxTI].id;
				newFunc = new function;
				newFunc->returnType = idtable.table[lextable.table[i].idxTI].iddatatype;
				++i;
				while (lextable.table[i].lexema[0] != LEX_RIGHTHESIS)
				{
					if (lextable.table[i].lexema[0] == LEX_ID)
					{
						newParam = new parametr;
						newParam->name = idtable.table[lextable.table[i].idxTI].id;
						newParam->type = idtable.table[lextable.table[i].idxTI].iddatatype;
						newFunc->parametrs.push_back(*newParam);
					}
					++i;
				}
				newFunc->parametrCount = newFunc->parametrs.size();
				sa.functions[currentName] = *newFunc;
				break;
			case LEX_PROC:
				i++;
				currentName = idtable.table[lextable.table[i].idxTI].id;
				newFunc = new function;
				newFunc->returnType = IT::IDDATATYPE::NONE;
				++i;
				while (lextable.table[i].lexema[0] != LEX_RIGHTHESIS)
				{
					if (lextable.table[i].lexema[0] == LEX_ID)
					{
						newParam = new parametr;
						newParam->name = idtable.table[lextable.table[i].idxTI].id;
						newParam->type = idtable.table[lextable.table[i].idxTI].iddatatype;
						newFunc->parametrs.push_back(*newParam);
					}
					++i;
				}
				newFunc->parametrCount = newFunc->parametrs.size();
				sa.functions[currentName] = *newFunc;
				break;
			case LEX_EXTR:
				if (isOpen) throw ERROR_THROW_IN(302, lextable.table[i].sn, 0);
				i += 2;
				currentName = idtable.table[lextable.table[i].idxTI].id;
				if (sa.standartFuncInfo.count(currentName) == 0) throw ERROR_THROW_IN(303, lextable.table[i].sn, 0);
				newFunc = new function;
				newFunc->returnType = idtable.table[lextable.table[i].idxTI].iddatatype;
				if(sa.standartFuncInfo[currentName].returnType != newFunc->returnType)throw ERROR_THROW_IN(305, lextable.table[i].sn, 0)
				++i;
				currentParamIdx = 0;
				while (lextable.table[i].lexema[0] != LEX_RIGHTHESIS && currentParamIdx < sa.standartFuncInfo[currentName].parametrCount)
				{
					if (lextable.table[i].lexema[0] == LEX_ID)
					{
						newParam = new parametr;
						newParam->name = idtable.table[lextable.table[i].idxTI].id;
						newParam->type = idtable.table[lextable.table[i].idxTI].iddatatype;
						if (newParam->type != sa.standartFuncInfo[currentName].parametrs[currentParamIdx].type)
							throw ERROR_THROW_IN(300, lextable.table[i].sn, 0);
						newFunc->parametrs.push_back(*newParam);
						currentParamIdx++;
					}
					++i;
				}
				if (lextable.table[i].lexema[0] != LEX_RIGHTHESIS || currentParamIdx < sa.standartFuncInfo[currentName].parametrCount)
					throw ERROR_THROW_IN(301, lextable.table[i].sn, 0);
				newFunc->parametrCount = newFunc->parametrs.size();
				
				sa.functions[currentName] = *newFunc;
				break;
			case LEX_CALL:
 				i++;
				currentName = idtable.table[lextable.table[i].idxTI].id;
				++i;
				currentParamIdx = 0;
				while (lextable.table[i].lexema[0] != SEQ && currentParamIdx < sa.functions[currentName].parametrCount)
				{
					if (lextable.table[i].lexema[0] == LEX_ID || lextable.table[i].lexema[0] == LEX_LITERAL)
					{
						if (idtable.table[lextable.table[i].idxTI].iddatatype != sa.functions[currentName].parametrs[currentParamIdx].type)
							throw ERROR_THROW_IN(300, lextable.table[i].sn, 0);
						currentParamIdx++;
					}
					++i;
				}
				if (lextable.table[i].lexema[0] != SEQ || currentParamIdx != sa.functions[currentName].parametrCount) 
					throw ERROR_THROW_IN(301, lextable.table[i].sn, 0);

				sa.dataTypeHistory.push(sa.functions[currentName].returnType);
				break;
			case LEX_ID:
			case LEX_LITERAL:
				if (isRet && idtable.table[lextable.table[i].idxTI].iddatatype != sa.functions[currentName].returnType)
					throw ERROR_THROW_IN(310, lextable.table[i].sn, 0);
				sa.dataTypeHistory.push(idtable.table[lextable.table[i].idxTI].iddatatype);
				break;
			case LEX_OPERATION:
				if (!sa.dataTypeHistory.empty())
				{
					firstType = sa.dataTypeHistory.top();
					sa.dataTypeHistory.pop();
				}
				else throw ERROR_THROW_IN(306, lextable.table[i].sn, 0);

				if (!sa.dataTypeHistory.empty())
				{
					secondType = sa.dataTypeHistory.top();
					sa.dataTypeHistory.pop();
				}
				else if (idtable.table[lextable.table[i].idxTI].id[0] == '-')
					continue;
				else throw ERROR_THROW_IN(306, lextable.table[i].sn, 0);
								
				if (firstType != secondType)throw ERROR_THROW_IN(304, lextable.table[i].sn, 0);
				if(sa.operatorsInfo[idtable.table[lextable.table[i].idxTI].id[0]].count(secondType) == 0)throw ERROR_THROW_IN(308, lextable.table[i].sn, 0);
				sa.dataTypeHistory.push(secondType);
				break;
			case LEX_EQUALL:
				if (!sa.dataTypeHistory.empty())
				{
					firstType = sa.dataTypeHistory.top();
					sa.dataTypeHistory.pop();
				}
				else throw ERROR_THROW_IN(306, lextable.table[i].sn, 0);
				
				
				if (lextable.table[i + 1].lexema[0] == LEX_CALL)secondType = idtable.table[lextable.table[i + 2].idxTI].iddatatype;
				else secondType = idtable.table[lextable.table[i + 1].idxTI].iddatatype;
				
				if (firstType != secondType)throw ERROR_THROW_IN(304, lextable.table[i].sn, 0);
				
				break;
			case LEX_SEMICOLON:
				isRet = false;
				while (!sa.dataTypeHistory.empty())sa.dataTypeHistory.pop();
				break;
			case LEX_CYCLE:
				isCycle = true;
				break;
			case LEX_LEFTBRACE:
				if (!isCycle)
				{
					if (isOpen) throw ERROR_THROW_IN(302, lextable.table[i].sn, 0);
					isOpen = true;
				}
				else
				{
					if(isCycleOpen)throw ERROR_THROW_IN(302, lextable.table[i].sn, 0);
					isCycleOpen = true;
				}
				break;
			case LEX_BRACELET:
				if (!isCycle)
				{
					if (!isOpen)throw ERROR_THROW_IN(307, lextable.table[i].sn, 0);
					isOpen = false;
				}
				else
				{
					if (!isCycleOpen)throw ERROR_THROW_IN(307, lextable.table[i].sn, 0);
					isCycle = false;
					isCycleOpen = false;
				}
				break;
			case LEX_RETURN:
				isRet = true;
				break;
			default:
				break;
			}
		}
		if (isOpen || isCycleOpen)throw ERROR_THROW_IN(302, lextable.size, 0);

		return result;
	}
};