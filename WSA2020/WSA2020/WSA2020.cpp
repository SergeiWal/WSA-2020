#include "includelib.h"
#include "Log.h"
#include "In.h"
#include "Lex.h"
#include  "MFST.h"
#include "PBN.h"
#include "CG.h"

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "ru");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, "Логический анализатор: ", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		LEX::LEX lex;
		lex.lextable = LT::Create(LT_MAXSIZE);
		lex.idtable = IT::Create(in.text.size());
		LEX::TableFill(in, lex);
		LEX::LexTableOut(lex.lextable, lex.idtable);
		LEX::IdTableOut(lex.idtable);
		MFST_TRACE_START
			MFST::Mfst mfst(lex, GRB::getGreibach());
		mfst.start();
		mfst.savededucation();
		mfst.printrules();
		PBN::BuildCodeInPN(lex);
		LEX::LexTableOut(lex.lextable, lex.idtable);
		LEX::IdTableOut(lex.idtable);
		std::ofstream* file = CG::CreateAsmFile();
		CG::ExtrnFuncAdd(file, lex.idtable, lex.lextable);
		CG::ConstBlockFill(file, lex.idtable);
		CG::DataBLockFILL(file, lex.idtable);
		CG::CodeBlockFILL(file, lex.idtable, lex.lextable);
		CG::asmMain(file);
		CG::CloseFile(file);
		Log::WriteIn(log, in);
		std::cout << std::endl;
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
    return 0;
}
