#pragma once

#include <fstream>

#include "includelib.h"
#include "Lex.h"
#include "MFST.h"
#include "Error.h"

#define FILENAME "gen.asm"
#define PROC_SERIES ".586"
#define MODEL ".model flat, stdcall"
#define LIBRARY "includelib kernel32.lib\n"\
				"includelib libucrt.lib\n"
#define EXIT_PROC "ExitProcces PROTO :DWORD"
#define STACK ".stack 4096"
#define CONST ".const"
#define BYTE "byte"
#define SHORT "sword"
#define TRUE '1'
#define FALSE '0'
#define DATA ".data"
#define RET "ret_"
#define CODE_BLOCK ".code"
#define SAVE_REGISTRS "uses eax ebx ecx edi esi "


namespace CG
{
	std::ofstream* CreateAsmFile();
	void ConstBlockFill(std::ofstream* file, IT::IdTable it);
	void SetDataValue(std::ofstream* file, IT::IdTable it, int pos);
	void DataBLockFILL(std::ofstream* file, IT::IdTable it);
	void generationOperation(std::ofstream* file, char opr, IT::IDDATATYPE type, int number, bool isBinary );
	void CodeBlockFILL(std::ofstream* file, IT::IdTable it, LT::LexTable lt);
	void asmMain(std::ofstream* file);
	void CloseFile(std::ofstream* file);
};