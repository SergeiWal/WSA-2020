#pragma once

#include <fstream>
#include <map>

#include "includelib.h"
#include "Lex.h"
#include "MFST.h"
#include "Error.h"

#define MAIN_NAME "WSA2020"
#define FILENAME "gen.asm"
#define ASM_HEADER	".586\n.model flat, stdcall\n"\
					"includelib libucrt.lib\n"\
					"includelib kernel32.lib\n"\
					"includelib WSA2020Lib.lib\n"\
					"ExitProcess PROTO :DWORD\n"\
					"SetConsoleOutputCP PROTO :DWORD\n"

#define STLIB_FUNC  "EXTRN concat :proc\n"\
					"EXTRN writeNumberBin :proc\n"\
					"EXTRN writeStr :proc\n"\
					"EXTRN writeBool :proc\n"\
					"EXTRN stringEquel :proc\n"
#define STACK ".stack 4096\n"
#define CONST ".const\n"
#define BYTE "byte"
#define WORD "word"
#define SHORT "sword"
#define TRUE '1'
#define FALSE '0'
#define DATA ".data"
#define CODE_BLOCK ".code"
#define BASE_RECOVERY "mov esp, ebp\n pop ebp"
#define W1251_SET "push 1251\n call SetConsoleOutputCP\n"

#define OWERFLOW_MESSAGE "overflowstring byte \"Ошибка: возникло переполнение при арифметической операции\",0"
#define OVERFLOW "OVERFLOW:\n push offset overflowstring\n push lengthof overflowstring\n call writeStr\n push -1\n call ExitProcess\n"
#define ZERODIV_MESSAGE "zeroerror byte \"Ошибка: деление на ноль\",0"
#define ZERODIV "ZERODIV:\n push offset zeroerror\n push lengthof zeroerror\n call writeStr\n push -1\n call ExitProcess\n"

#define EXTRN_FUNC_CONNECT(id) "EXTRN " << id << " :proc\n"
#define GET_ID(vr,id) vr << '_' << id
#define GET_TYPE_VALUE(t,v) ' ' << t << ' ' << v
#define GET_TYPE_VALUE_STR(v) " byte \"" << v << "\", 0";
#define DEFAULT_STR_INIT " byte 255 dup (0), 0"
#define DEFAULT_CHAR_INIT " byte 0, 0"
#define GET_RET_VARIABLE(i) "ret_"<<i;
#define PUSH(vr,id) "push " << vr << '_' << id
#define PUSH_STR(vr,id) "push offset " << vr << '_' << id << "\npush lengthof "  << vr << '_' << id
#define PARAM_TRANS(vr, id, dest) "mov ax," << vr << '_' << id <<"\nmov "<<dest<<",ax "
#define PARAM_STR_TRANS(vr, id, dest) "cld\n mov ecx, lengthof "  << vr << '_' << id << "\nlea edi,"<<dest<<"\nlea esi,"<< vr << '_' << id <<"\nrep movsb\n"
#define EXTR_PARAM(id) "push " << id
#define EXTR_PARAM_STR(id) "push offset "<<id<<"\npush lengthof "<<id
#define EXTR_RET "push ax\n"
#define EXTR_RET_STR "push offset eax\n push lengthof eax\n"
#define RET_VALUE(id) "push ret_"<<id
#define RET_STR(id) "push offset ret_"<<id<<"\npush lengthof ret_"<<id
#define POP(vr,id) "pop "<< vr << '_' << id
#define POP_STR(vr,id) "cld\npop ecx\npop esi\nlea edi,"<< vr << '_' << id<<"\nrep movsb\n"
#define FUNC_RET(id) "pop ax\nmov ret_" << id <<",ax\n"
#define FUNC_RET_STR(id) "cld\npop ecx\npop esi\nlea edi, ret_"<<id<<"\nrep movsb\n"
#define WRITE_INT "call writeNumberBin\n"
#define WRITE_BOOL "call writeBool\n"
#define WRITE_STR "call writeStr\n"
#define WRITE_CHAR "call writeStr\n"
#define FUNC_HEADER(id) id << " PROC uses eax ebx ecx edi esi\n push ebp\n mov ebp, esp\n"
#define CYCLE_HEADER(id) "pop eax\ncmp eax,1\njz "<<id<<"_BEGIN\njnz "<<id<<"_END\n"<<id<<"_BEGIN:\n"
#define CYCLE_FOOTER(id) "jmp "<<id<<"\n"<<id<<"_END:\n"
#define ASM_MAIN "main PROC \n\n\n push 1251\n call SetConsoleOutputCP\ncall WSA2020\n push 0h\ncall ExitProcess\n main ENDP\nend main"



#define EXPR_INT_PLUS "pop bx\npop ax\nadd ax,bx\njo OVERFLOW\npush ax\n"
#define EXPR_STR_CONCAT "call concat\npush eax\npush 256\n"
#define EXPR_INT_DIFF "pop bx\npop ax\nsub ax,bx\njo OVERFLOW\npush ax\n"
#define EXPR_INT_NEG "pop ax\nneg ax\npush ax\n"
#define EXPR_MUL "pop bx\npop ax\nimul bx\njo OVERFLOW\npush ax\n"
#define EXPR_DIV "pop bx\npop ax\nmov dx,0\ncmp bx,0\njz ZERODIV\nidiv bx\npush ax\n"
#define EXPR_MOD "pop bx\npop ax\nmov dx,0\ncmp bx,0\njz ZERODIV\nidiv bx\npush dx\n" 

#define EXPR_INT_LESS(n) "pop bx\npop ax\ncmp ax,bx\njs true_"<<n <<"\npush 0\njmp end_"<<n<<"\ntrue_"<<n<<": \npush 1\nend_"<<n<<": \n"
#define EXPR_INT_MORE(n) "pop bx\npop ax\ncmp ax,bx\njns true_"<<n <<"\npush 0\njmp end_"<<n<<"\ntrue_"<<n<<": \npush 1\nend_"<<n<<": \n"
#define EXPR_STR_LESS(n) "call stringEquel\npush eax\ncmp eax,1\njnz true_"<<n <<"\npush 0\njmp end_"<<n<<"\ntrue_"<<n<<": \npush 1\nend_"<<n<<": \n"
#define EXPR_STR_MORE(n) "call stringEquel\npush eax\ncmp eax,1\njz true_"<<n <<"\npush 0\njmp end_"<<n<<"\ntrue_"<<n<<": \npush 1\nend_"<<n<<": \n"
#define EXPR_INT_EQUEL(n) "pop bx\npop ax\n cmp ax,bx\njz true_"<<n <<"\npush 0\njmp end_"<<n<<"\ntrue_"<<n<<": \npush 1\nend_"<<n<<": \n"
#define EXPR_INT_NOT_EQUEL(n) "pop bx\npop ax\n cmp ax,bx\njnz true_"<<n <<"\npush 0\njmp end_"<<n<<"\ntrue_"<<n<<": \npush 1\nend_"<<n<<": \n"
#define EXPR_STR_EQUEL(n) "call stringEquel\npush eax\ncmp eax,0\njz true_"<<n <<"\npush 0\njmp end_"<<n<<"\ntrue_"<<n<<": \npush 1\nend_"<<n<<": \n"
#define EXPR_STR_NOT_EQUEL(n) "call stringEquel\npush eax\ncmp eax,1\njnz true_"<<n <<"\npush 0\njmp end_"<<n<<"\ntrue_"<<n<<": \npush 1\nend_"<<n<<": \n"




namespace CG
{
	struct Parametr
	{
		std::string name;
		IT::IDDATATYPE type;

		Parametr(std::string nm, IT::IDDATATYPE tp);
	};


	std::ofstream* CreateAsmFile();
	void ExtrnFuncAdd(std::ofstream* file, IT::IdTable it, LT::LexTable lt);
	void ConstBlockFill(std::ofstream* file, IT::IdTable it);
	void SetDataValue(std::ofstream* file, IT::IdTable it, int pos);
	void DataBLockFILL(std::ofstream* file, IT::IdTable it);
	void generationOperation(std::ofstream* file, char opr, IT::IDDATATYPE type, int number, bool isBinary );
	void CodeBlockFILL(std::ofstream* file, IT::IdTable it, LT::LexTable lt);
	void CloseFile(std::ofstream* file);
};