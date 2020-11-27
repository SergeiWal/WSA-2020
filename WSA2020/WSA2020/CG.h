#pragma once

#include <fstream>

#include "includelib.h"
#include "Lex.h"
#include "MFST.h"
#include "Error.h"

#define FILENAME "gen.asm"
#define PROC_SERIES ".586"
#define MODEL ".model flat, stdcall"
#define KERNEL_LIB "includelib kernel32.lib"
#define EXIT_PROC "ExitProcces PROTO :DWORD"
#define STACK ".stack 4096"
#define CONST ".const"
#define RET "ret_"
#define BYTE "byte"
#define WORD_TYPE "word"
#define TRUE '1'
#define FALSE '0'


namespace CG
{
	std::ofstream* CreateAsmFile();
	void ConstBlockFill(std::ofstream* file, IT::IdTable it);
	void DataBLockFILL(std::ofstream* file, IT::IdTable it);
	void CloseFile(std::ofstream* file);
};