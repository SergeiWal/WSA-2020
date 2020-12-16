#include "PBN.h"

namespace PBN
{
	int SearchExpressionPos(int startPos, const LT::LexTable& lt)
	{
		for (int i = startPos; i < lt.size; ++i)
		{
			if (lt.table[i].lexema[0] == LEX_EQUALL && lt.table[i + 1].lexema[0] == LEX_CALL)
				return i + 2;
			else if (lt.table[i].lexema[0] == LEX_EQUALL || lt.table[i].lexema[0] == LEX_CALL)
				return i + 1;
			else if(lt.table[i].lexema[0] == LEX_OPERATION)
				for (; ; i--) 
					if (lt.table[i].lexema[0] == LEX_SEMICOLON)
						return i + 2;
		}	
		return -1;
	}

	PBN* CreatePN(int pos, LEX::LEX& lex)
	{
		std::stack<LT::Entry*> stack;
		PBN* expression = new PBN;
		expression->size = 0;

		LT::Entry* it_in_table = &lex.lextable.table[pos];

		IT::IDTYPE idtype = IT::IDTYPE::NONE;
		int seqLen;

		while (it_in_table->lexema[0] != LEX_SEMICOLON && it_in_table->lexema[0] != LEX_LEFTBRACE)
		{ 
			char opr = NONE_OPERATOR;

			if (it_in_table->lexema[0] == LEX_OPERATION)opr = lex.idtable.table[it_in_table->idxTI].id[0];
			else if (it_in_table->lexema[0] == LEX_LEFTHESIS || it_in_table->lexema[0] == LEX_RIGHTHESIS ||
				it_in_table->lexema[0] == LEX_COMA)opr = it_in_table->lexema[0];

			std::map<char, int>::iterator map_it = expression->operators.find(opr);

			if (map_it == expression->operators.end())
			{
				if (it_in_table->idxTI != LT_IT_NULLIDX)
				{
					expression->result[expression->size++] = *it_in_table;

					if (lex.idtable.table[it_in_table->idxTI].idtype == IT::IDTYPE::F ||
						lex.idtable.table[it_in_table->idxTI].idtype == IT::IDTYPE::P
						|| lex.idtable.table[it_in_table->idxTI].idtype == IT::IDTYPE::E)
					{
						idtype = lex.idtable.table[it_in_table->idxTI].idtype;
						seqLen = 0;
					}
					else if (idtype == IT::IDTYPE::F || idtype == IT::IDTYPE::P || idtype == IT::IDTYPE::E)seqLen++;
				}
			}
			else if (opr == LEX_LEFTHESIS)stack.push(it_in_table);
			else if (opr == LEX_RIGHTHESIS)
			{

				while (!stack.empty() && stack.top()->lexema[0] != LEX_LEFTHESIS)
				{
					expression->result[expression->size++] = *stack.top();
					stack.pop();
				}
				if (!stack.empty())stack.pop();

				if (idtype == IT::IDTYPE::F || idtype == IT::IDTYPE::P || idtype == IT::IDTYPE::E)
				{
					LT::Entry* specEntry = new LT::Entry;
					IT::Entry* countParam = new IT::Entry;

					specEntry->idxTI = LT_IT_NULLIDX;
					LEX::SetNewLtNodeValue(*specEntry, SEQ);
					specEntry->sn = it_in_table->sn;
					
					countParam->iddatatype = IT::IDDATATYPE::INT;
					countParam->idtype = IT::IDTYPE::L;
					countParam->visibilityRegion = GLOBAL_VISIBLE;
					countParam->value.vint = seqLen;
					specEntry->idxTI = IT::IsId(lex.idtable, *countParam);

					if (specEntry->idxTI == TI_NULLIDX)
					{
						LEX::SetLiteralName(*countParam, pos);
						specEntry->idxTI = lex.idtable.size;
						countParam->idxfirstLE = lex.lextable.size;
						IT::Add(lex.idtable, *countParam);
					}
					expression->result[expression->size++] = *specEntry;
					

					idtype = IT::IDTYPE::NONE;
					seqLen = 0;
				}

			}
			else if (opr == LEX_COMA)
			{
				while (!stack.empty() && expression->operators[stack.top()->lexema[0]] >= expression->operators[opr])
				{
					expression->result[expression->size++] = *stack.top();
					stack.pop();
				}
			}
			else if ((stack.empty() || stack.top()->lexema[0] == LEX_LEFTHESIS) && opr != LEX_COMA)stack.push(it_in_table);
			else
			{
				while (!stack.empty() && expression->operators[stack.top()->lexema[0]] >= expression->operators[opr])
				{
					expression->result[expression->size++] = *stack.top();
					stack.pop();
				}
				stack.push(it_in_table);

			}

			it_in_table++;

		}

		while (!stack.empty())
		{
			expression->result[expression->size++] = *stack.top();
			stack.pop();
		}
		return expression;
	}

	bool BuildCodeInPN(LEX::LEX& lex)
	{
		int pos = SearchExpressionPos(0, lex.lextable);
		while (pos != -1)
		{
			PBN* expression = new PBN;
			expression = CreatePN(pos, lex);
			for (int i = 0; i < expression->size; ++i, ++pos)
			{
				lex.lextable.table[pos].lexema[0] = expression->result[i].lexema[0];
				lex.lextable.table[pos].idxTI = expression->result[i].idxTI;
				lex.lextable.table[pos].sn = expression->result[i].sn;
				if(lex.lextable.table[pos].idxTI != LT_IT_NULLIDX)
					lex.idtable.table[lex.lextable.table[pos].idxTI].idxfirstLE = pos;
			}

			while (lex.lextable.table[pos].lexema[0] != LEX_SEMICOLON && lex.lextable.table[pos].lexema[0] != LEX_LEFTBRACE)
			{
				lex.lextable.table[pos].lexema[0] = NULL;
				lex.lextable.table[pos].idxTI = LT_IT_NULLIDX;
				pos++;
			}
			pos = SearchExpressionPos(pos, lex.lextable);
		}
		return true;
	}

};