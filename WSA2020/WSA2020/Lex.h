#pragma once

#include <stack>
#include <set>

#include "Error.h"
#include "In.h"
#include "FST.h"
#include "LT.h"
#include "IT.h"

#define SEQ '@'

#define TOKENS_ARRAY_SIZE 15

#define STRING			7,\
						FST::NODE(1, FST::RELATION('s', 1)),\
						FST::NODE(1, FST::RELATION('t', 2)),\
						FST::NODE(1, FST::RELATION('r', 3)),\
						FST::NODE(1, FST::RELATION('i', 4)),\
						FST::NODE(1, FST::RELATION('n', 5)),\
						FST::NODE(1, FST::RELATION('g', 6)),\
						FST::NODE()
#define SHORT			6,\
						FST::NODE(1, FST::RELATION('s', 1)),\
						FST::NODE(1, FST::RELATION('h', 2)),\
						FST::NODE(1, FST::RELATION('o', 3)),\
						FST::NODE(1, FST::RELATION('r', 4)),\
						FST::NODE(1, FST::RELATION('t', 5)),\
						FST::NODE()
#define BOOL			5,\
						FST::NODE(1, FST::RELATION('b', 1)),\
						FST::NODE(1, FST::RELATION('o', 2)),\
						FST::NODE(1, FST::RELATION('o', 3)),\
						FST::NODE(1, FST::RELATION('l', 4)),\
						FST::NODE()
#define NUMB_LITERAL	5,\
						FST::NODE(2, FST::RELATION('0', 1), FST::RELATION('1', 1)),\
						FST::NODE(2, FST::RELATION('b', 2), FST::RELATION('o', 3)),\
						FST::NODE(4, FST::RELATION('0', 2), FST::RELATION('1', 2), FST::RELATION('0', 4), FST::RELATION('1', 4)),\
						FST::NODE(14, FST::RELATION('0', 3), FST::RELATION('1', 3), FST::RELATION('2', 3), FST::RELATION('3', 3),\
						FST::RELATION('4', 3), FST::RELATION('5', 3), FST::RELATION('6', 3), FST::RELATION('7', 3),\
						FST::RELATION('0', 4), FST::RELATION('1', 4), FST::RELATION('2', 4), FST::RELATION('3', 4),\
						FST::RELATION('4', 4), FST::RELATION('5', 4), FST::RELATION('6', 4), FST::RELATION('7', 4)),\
						FST::NODE()
#define STR_LITERAL		3,\
						FST::NODE(1, FST::RELATION('\'', 1)),\
						FST::NODE(142, FST::RELATION('a', 1),FST::RELATION('b', 1),FST::RELATION('c', 1),FST::RELATION('d', 1),\
						FST::RELATION('e', 1),FST::RELATION('f', 1), FST::RELATION('g', 1),FST::RELATION('h', 1), FST::RELATION('i', 1), FST::RELATION('j', 1),FST::RELATION('k', 1),FST::RELATION('l', 1),FST::RELATION('m', 1),\
						FST::RELATION('n', 1),FST::RELATION('o', 1),FST::RELATION('p', 1),FST::RELATION('q', 1),FST::RELATION('r', 1), FST::RELATION('s', 1),FST::RELATION('t', 1),FST::RELATION('u', 1),FST::RELATION('v', 1),FST::RELATION('w', 1),FST::RELATION('x', 1),FST::RELATION('y', 1),FST::RELATION('z', 1),\
						FST::RELATION('A', 1), FST::RELATION('B', 1), FST::RELATION('C', 1), FST::RELATION('D', 1), \
						FST::RELATION('E', 1), FST::RELATION('F', 1), FST::RELATION('G', 1), FST::RELATION('H', 1), FST::RELATION('I', 1), FST::RELATION('J', 1), FST::RELATION('K', 1), FST::RELATION('L', 1), FST::RELATION('M', 1), \
						FST::RELATION('N', 1), FST::RELATION('O', 1), FST::RELATION('P', 1), FST::RELATION('Q', 1), FST::RELATION('R', 1), FST::RELATION('S', 1), FST::RELATION('T', 1), FST::RELATION('U', 1), FST::RELATION('V', 1), FST::RELATION('W', 1), FST::RELATION('X', 1), FST::RELATION('Y', 1), FST::RELATION('Z', 1),\
						FST::RELATION('à', 1), FST::RELATION('á', 1), FST::RELATION('â', 1), FST::RELATION('ã', 1),\
						FST::RELATION('ä', 1), FST::RELATION('å', 1), FST::RELATION('¸', 1), FST::RELATION('æ', 1), FST::RELATION('ç', 1), FST::RELATION('è', 1), FST::RELATION('é', 1), FST::RELATION('ê', 1), FST::RELATION('ë', 1), \
						FST::RELATION('ì', 1), FST::RELATION('í', 1), FST::RELATION('î', 1), FST::RELATION('ï', 1), FST::RELATION('ð', 1), FST::RELATION('ñ', 1), FST::RELATION('ò', 1), FST::RELATION('ó', 1), FST::RELATION('ô', 1), FST::RELATION('õ', 1), FST::RELATION('ö', 1), FST::RELATION('÷', 1), FST::RELATION('ø', 1), \
						FST::RELATION('ù', 1), FST::RELATION('Ú', 1), FST::RELATION('û', 1), FST::RELATION('ü', 1), FST::RELATION('ý', 1), FST::RELATION('þ', 1), FST::RELATION('ÿ', 1),\
						FST::RELATION('À', 1), FST::RELATION('Á', 1), FST::RELATION('Â', 1), FST::RELATION('Ã', 1), \
						FST::RELATION('Ä', 1), FST::RELATION('Å', 1), FST::RELATION('¨', 1), FST::RELATION('Æ', 1), FST::RELATION('Ç', 1), FST::RELATION('È', 1), FST::RELATION('É', 1), FST::RELATION('Ê', 1), FST::RELATION('Ë', 1), \
						FST::RELATION('Ì', 1), FST::RELATION('Í', 1), FST::RELATION('Î', 1), FST::RELATION('Ï', 1), FST::RELATION('Ð', 1), FST::RELATION('Ñ', 1), FST::RELATION('Ò', 1), FST::RELATION('Ó', 1), FST::RELATION('Ô', 1), FST::RELATION('Õ', 1), FST::RELATION('Ö', 1), FST::RELATION('×', 1), FST::RELATION('Ø', 1), \
						FST::RELATION('Ù', 1), FST::RELATION('Ú', 1), FST::RELATION('Û', 1), FST::RELATION('Ü', 1), FST::RELATION('Ý', 1), FST::RELATION('Þ', 1), FST::RELATION('ß', 1),\
						FST::RELATION(',', 1), FST::RELATION('.', 1), FST::RELATION(':', 1), FST::RELATION(';', 1),\
						FST::RELATION('!', 1), FST::RELATION('?', 1), FST::RELATION('+', 1), FST::RELATION('-', 1),\
						FST::RELATION('/', 1), FST::RELATION('*', 1), FST::RELATION('(', 1), FST::RELATION(')', 1), FST::RELATION('0', 1), \
						FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1), \
						FST::RELATION('6', 1), FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1),FST::RELATION(' ', 1), FST::RELATION('\'', 2)),\
						FST::NODE()
#define BOOL_LITERAL	8,\
						FST::NODE(2, FST::RELATION('t', 1),FST::RELATION('f', 3)),\
						FST::NODE(1, FST::RELATION('r', 2)),\
						FST::NODE(1, FST::RELATION('u', 6)),\
						FST::NODE(1, FST::RELATION('a', 4)),\
						FST::NODE(1, FST::RELATION('l', 5)),\
						FST::NODE(1, FST::RELATION('s', 6)),\
						FST::NODE(1, FST::RELATION('e', 7)),\
						FST::NODE()
#define VAR				4,\
						FST::NODE(1, FST::RELATION('v', 1)),\
						FST::NODE(1, FST::RELATION('a', 2)),\
						FST::NODE(1, FST::RELATION('r', 3)),\
						FST::NODE()
#define MAIN			5,\
						FST::NODE(1, FST::RELATION('m', 1)),\
						FST::NODE(1, FST::RELATION('a', 2)),\
						FST::NODE(1, FST::RELATION('i', 3)),\
						FST::NODE(1, FST::RELATION('n', 4)),\
						FST::NODE()
#define FUNC			5,\
						FST::NODE(1, FST::RELATION('f', 1)),\
						FST::NODE(1, FST::RELATION('u', 2)),\
						FST::NODE(1, FST::RELATION('n', 3)),\
						FST::NODE(1, FST::RELATION('c', 4)),\
						FST::NODE()
#define PROC			5,\
						FST::NODE(1, FST::RELATION('p', 1)),\
						FST::NODE(1, FST::RELATION('r', 2)),\
						FST::NODE(1, FST::RELATION('o', 3)),\
						FST::NODE(1, FST::RELATION('c', 4)),\
						FST::NODE()
#define RET				4,\
						FST::NODE(1, FST::RELATION('r', 1)),\
						FST::NODE(1, FST::RELATION('e', 2)),\
						FST::NODE(1, FST::RELATION('t', 3)),\
						FST::NODE()
#define CYCLE			6,\
						FST::NODE(1, FST::RELATION('w', 1)),\
						FST::NODE(1, FST::RELATION('h', 2)),\
						FST::NODE(1, FST::RELATION('i', 3)),\
						FST::NODE(1, FST::RELATION('l', 4)),\
						FST::NODE(1, FST::RELATION('e', 5)),\
						FST::NODE()
#define WRITE			6,\
						FST::NODE(1, FST::RELATION('w', 1)),\
						FST::NODE(1, FST::RELATION('r', 2)),\
						FST::NODE(1, FST::RELATION('i', 3)),\
						FST::NODE(1, FST::RELATION('t', 4)),\
						FST::NODE(1, FST::RELATION('e', 5)),\
						FST::NODE()
#define OPERATION       3,\
						FST::NODE(9, FST::RELATION('=', 1), FST::RELATION('!', 1), FST::RELATION('+', 2), FST::RELATION('-', 2),\
						FST::RELATION('*', 2),FST::RELATION('/', 2),FST::RELATION('%', 2),FST::RELATION('<', 2),FST::RELATION('>', 2)),\
						FST::NODE(1, FST::RELATION('=', 2)),\
						FST::NODE()

#define ID              3,\
						FST::NODE(104, FST::RELATION('a', 1), FST::RELATION('b', 1), FST::RELATION('c', 1), FST::RELATION('d', 1),\
						FST::RELATION('e', 1),  FST::RELATION('f', 1),  FST::RELATION('g', 1), FST::RELATION('h', 1), FST::RELATION('i', 1), FST::RELATION('j', 1), FST::RELATION('k', 1), FST::RELATION('l', 1), FST::RELATION('m', 1),\
						FST::RELATION('n', 1),FST::RELATION('o', 1),FST::RELATION('p', 1),FST::RELATION('q', 1),FST::RELATION('r', 1), FST::RELATION('s', 1), FST::RELATION('t', 1), FST::RELATION('u', 1), FST::RELATION('v', 1), FST::RELATION('w', 1),\
						FST::RELATION('x', 1),FST::RELATION('y', 1),FST::RELATION('z', 1),\
						FST::RELATION('A', 1),FST::RELATION('B', 1),FST::RELATION('C', 1),FST::RELATION('D', 1),\
						FST::RELATION('E', 1),FST::RELATION('F', 1), FST::RELATION('G', 1),FST::RELATION('H', 1), FST::RELATION('I', 1), FST::RELATION('J', 1),FST::RELATION('K', 1),FST::RELATION('L', 1),FST::RELATION('M', 1),\
						FST::RELATION('N', 1),FST::RELATION('O', 1),FST::RELATION('P', 1),FST::RELATION('Q', 1),FST::RELATION('R', 1), FST::RELATION('S', 1),FST::RELATION('T', 1),FST::RELATION('U', 1),FST::RELATION('V', 1),FST::RELATION('W', 1),FST::RELATION('X', 1),FST::RELATION('Y', 1),FST::RELATION('Z', 1),\
						FST::RELATION('a', 2), FST::RELATION('b', 2), FST::RELATION('c', 2), FST::RELATION('d', 2),\
						FST::RELATION('e', 2),  FST::RELATION('f', 2),  FST::RELATION('g', 2), FST::RELATION('h', 2), FST::RELATION('i', 2), FST::RELATION('j', 2), FST::RELATION('k', 2), FST::RELATION('l', 2), FST::RELATION('m', 2),\
						FST::RELATION('n', 2),FST::RELATION('o', 2),FST::RELATION('p', 2),FST::RELATION('q', 2),FST::RELATION('r', 2), FST::RELATION('s', 2), FST::RELATION('t', 2), FST::RELATION('u', 2), FST::RELATION('v', 2), FST::RELATION('w', 2),\
						FST::RELATION('x', 2),FST::RELATION('y', 2),FST::RELATION('z', 2),\
						FST::RELATION('A', 2),FST::RELATION('B', 2),FST::RELATION('C', 2),FST::RELATION('D', 2),\
						FST::RELATION('E', 2),FST::RELATION('F', 2), FST::RELATION('G', 2),FST::RELATION('H', 2), FST::RELATION('I', 2), FST::RELATION('J', 2),FST::RELATION('K', 2),FST::RELATION('L', 2),FST::RELATION('M', 2),\
						FST::RELATION('N', 2),FST::RELATION('O', 2),FST::RELATION('P', 2),FST::RELATION('Q', 2),FST::RELATION('R', 2), FST::RELATION('S', 2),FST::RELATION('T', 2),FST::RELATION('U', 2),FST::RELATION('V', 2),FST::RELATION('W', 2),FST::RELATION('X', 2),FST::RELATION('Y', 2),FST::RELATION('Z', 2)),\
						FST::NODE(114, FST::RELATION('a', 1), FST::RELATION('b', 1), FST::RELATION('c', 1), FST::RELATION('d', 1),\
						FST::RELATION('e', 1),  FST::RELATION('f', 1),  FST::RELATION('g', 1), FST::RELATION('h', 1), FST::RELATION('i', 1), FST::RELATION('j', 1), FST::RELATION('k', 1), FST::RELATION('l', 1), FST::RELATION('m', 1),\
						FST::RELATION('n', 1),FST::RELATION('o', 1),FST::RELATION('p', 1),FST::RELATION('q', 1),FST::RELATION('r', 1), FST::RELATION('s', 1), FST::RELATION('t', 1), FST::RELATION('u', 1), FST::RELATION('v', 1), FST::RELATION('w', 1),\
						FST::RELATION('x', 1),FST::RELATION('y', 1),FST::RELATION('z', 1),\
						FST::RELATION('A', 1),FST::RELATION('B', 1),FST::RELATION('C', 1),FST::RELATION('D', 1),\
						FST::RELATION('E', 1),FST::RELATION('F', 1), FST::RELATION('G', 1),FST::RELATION('H', 1), FST::RELATION('I', 1), FST::RELATION('J', 1),FST::RELATION('K', 1),FST::RELATION('L', 1),FST::RELATION('M', 1),\
						FST::RELATION('N', 1),FST::RELATION('O', 1),FST::RELATION('P', 1),FST::RELATION('Q', 1),FST::RELATION('R', 1), FST::RELATION('S', 1),FST::RELATION('T', 1),FST::RELATION('U', 1),FST::RELATION('V', 1),FST::RELATION('W', 1),FST::RELATION('X', 1),FST::RELATION('Y', 1),FST::RELATION('Z', 1),\
						FST::RELATION('a', 2), FST::RELATION('b', 2), FST::RELATION('c', 2), FST::RELATION('d', 2),\
						FST::RELATION('e', 2),  FST::RELATION('f', 2),  FST::RELATION('g', 2), FST::RELATION('h', 2), FST::RELATION('i', 2), FST::RELATION('j', 2), FST::RELATION('k', 2), FST::RELATION('l', 2), FST::RELATION('m', 2),\
						FST::RELATION('n', 2),FST::RELATION('o', 2),FST::RELATION('p', 2),FST::RELATION('q', 2),FST::RELATION('r', 2), FST::RELATION('s', 2), FST::RELATION('t', 2), FST::RELATION('u', 2), FST::RELATION('v', 2), FST::RELATION('w', 2),\
						FST::RELATION('x', 2),FST::RELATION('y', 2),FST::RELATION('z', 2),\
						FST::RELATION('A', 2),FST::RELATION('B', 2),FST::RELATION('C', 2),FST::RELATION('D', 2),\
						FST::RELATION('E', 2),FST::RELATION('F', 2), FST::RELATION('G', 2),FST::RELATION('H', 2), FST::RELATION('I', 2), FST::RELATION('J', 2),FST::RELATION('K', 2),FST::RELATION('L', 2),FST::RELATION('M', 2),\
						FST::RELATION('N', 2),FST::RELATION('O', 2),FST::RELATION('P', 2),FST::RELATION('Q', 2),FST::RELATION('R', 2), FST::RELATION('S', 2),FST::RELATION('T', 2),FST::RELATION('U', 2),FST::RELATION('V', 2),FST::RELATION('W', 2),FST::RELATION('X', 2),FST::RELATION('Y', 2),FST::RELATION('Z', 2),\
						FST::RELATION('0', 2),FST::RELATION('1', 2),FST::RELATION('2', 2),FST::RELATION('3', 2),FST::RELATION('4', 2),FST::RELATION('5', 2),FST::RELATION('6', 2),FST::RELATION('7', 2),FST::RELATION('8', 2),FST::RELATION('9', 2)),\
						FST::NODE()

#define TOKENS_ARRAY  {\
					  LexExample('s',FST::FST(SHORT),LexType::T),LexExample('s',FST::FST(STRING),LexType::T),\
					  LexExample('b',FST::FST(BOOL),LexType::T),LexExample('0',FST::FST(NUMB_LITERAL),LexType::L),\
					  LexExample('1',FST::FST(NUMB_LITERAL),LexType::L), LexExample('\'',FST::FST(STR_LITERAL),LexType::L),\
					  LexExample('t',FST::FST(BOOL_LITERAL),LexType::L), LexExample('f',FST::FST(BOOL_LITERAL),LexType::L),\
					  LexExample('v',FST::FST(VAR),LexType::V), LexExample('m',FST::FST(MAIN),LexType::M),\
					  LexExample('f',FST::FST(FUNC),LexType::F), LexExample('p',FST::FST(PROC),LexType::P),\
					  LexExample('r',FST::FST(RET),LexType::R), LexExample('w',FST::FST(CYCLE),LexType::C), \
					  LexExample('w',FST::FST(WRITE),LexType::W)} 
				
namespace LEX
{
	enum class LexType { T = 1, L = 2, V = 3, M = 4, F = 5, P = 6, R = 7, C = 8, W = 9, O = 10, I = 11 };
	
	struct LexExample
	{
		char firstSymbol;
		FST::FST fst;
		LexType type;

		LexExample(
			char firstCh,
			FST::FST nfst,
			LexType tp
		);
		
	};

	struct LEX
	{
		LT::LexTable lextable;
		IT::IdTable  idtable;
		std::set<char> one_symbol_lexems = { LEX_SEMICOLON,LEX_COMA,LEX_LEFTBRACE,LEX_BRACELET,LEX_LEFTHESIS,
												LEX_RIGHTHESIS,LEX_EQUALL, LEX_CALL };
	};

	LexType LAnaliz( In::word word);
	unsigned char* UchVectorToString(const std::vector<unsigned char>& word);

	void SetNewLtNodeValue(LT::Entry& entry, char value);
	IT::IDDATATYPE GetDataType(std::vector<unsigned char> word);
	void IsParametrSet(IT::Entry& ent, char nextCh);
	void ExitFromVisibleRegion(std::stack<std::string>& regions, char currentCh, bool isCycle);
	void SetDefaultValue(IT::Entry& ent);
	void SetLiteralValue(IT::Entry& ent, const std::vector<unsigned char>& word);
	void SetLiteralName(IT::Entry& ent, int number);
	void SetOperatorValue(IT::Entry& ent, char ch);

	int OctToInt(std::vector<unsigned char> word);
	int BinToInt(std::vector<unsigned char> word);

	void TableFill(In::IN in, LEX& lex);
	void LexTableOut(LT::LexTable lt, IT::IdTable it);
	void IdTableOut(IT::IdTable it);
}