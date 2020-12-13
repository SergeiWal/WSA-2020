#pragma once
#include "includelib.h"
#include "Lex.h"
#include <map>
#include <stack>
#include <set>



#define SFL_INFO	{"len", function(IT::IDDATATYPE::INT, 1, parametr("s",IT::IDDATATYPE::STR))} ,\
					{"random", function(IT::IDDATATYPE::INT, 2, parametr("a", IT::IDDATATYPE::INT),parametr("b", IT::IDDATATYPE::INT))},\
					{"writeOct", function(IT::IDDATATYPE::BL, 1, parametr("a",IT::IDDATATYPE::INT))}	
#define OPR_INFO	{'+', {IT::IDDATATYPE::INT,IT::IDDATATYPE::STR}},\
					{'-', {IT::IDDATATYPE::INT}},\
					{'*', {IT::IDDATATYPE::INT}},\
					{'/', {IT::IDDATATYPE::INT}},\
					{'%', {IT::IDDATATYPE::INT}},\
					{'=', {IT::IDDATATYPE::INT,IT::IDDATATYPE::STR,IT::IDDATATYPE::BL}},\
					{'!', {IT::IDDATATYPE::INT,IT::IDDATATYPE::STR,IT::IDDATATYPE::BL}},\
					{'<', {IT::IDDATATYPE::INT,IT::IDDATATYPE::STR}},\
					{'>', {IT::IDDATATYPE::INT,IT::IDDATATYPE::STR}}


//совпадение типов в выражении +
//совпадения количества параметров функции +
//совпадение типов параметров функции +
//наличие закрывающей скобки+
//проверка обьявлений функций стандартной либы +
//разрешена ли операция для данных типов
//глобальные переменные


namespace SA
{

	struct parametr
	{
		std::string name;
		IT::IDDATATYPE type;

		parametr() {};
		parametr(std::string nm, IT::IDDATATYPE tp);
	};
	struct function
	{
		
		std::vector<parametr> parametrs;
		IT::IDDATATYPE returnType;
		int parametrCount;

		function() {};
		function( IT::IDDATATYPE rt, int count, parametr parm ...);
	};

	struct SA
	{
		std::stack<IT::IDDATATYPE> dataTypeHistory;
		std::map<std::string, function> standartFuncInfo;
		std::map<std::string, function> functions;
		std::map<char, std::set<IT::IDDATATYPE>> operatorsInfo;
	};

	bool SemanticsAnaliz(IT::IdTable idtable, LT::LexTable lextable);
};