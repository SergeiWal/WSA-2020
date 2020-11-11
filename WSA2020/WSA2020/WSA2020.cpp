#include "includelib.h"
#include "Log.h"
#include "In.h"
#include "Lex.h"

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
		In::WriteInputTextInConsole(in);
		LEX::LEX lex;
		lex.lextable = LT::Create(in.text.size());
		lex.idtable = IT::Create(in.text.size());
		LEX::TableFilling(in, lex);
		LEX::LexTableOut(lex.lextable);
		Log::WriteIn(log, in);
		std::cout << std::endl;
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
    return 0;
}
