#include "includelib.h"
#include "Log.h"
#include "In.h"
#include "Lex.h"
#include  "MFST.h"
#include "PBN.h"
#include "Semantics.h"
#include "CG.h"

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "ru");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, "WSA2020: ", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		LEX::LEX lex;
		lex.lextable = LT::Create(LT_MAXSIZE);
		lex.idtable = IT::Create(in.text.size());
		LEX::TableFill(in, lex);
		*log.stream << std::internal << std::setfill('-') << std::setw(48) << "LEX TABLE" << std::setw(48) << "" << std::endl;
		LEX::LexTableOut(log.stream, lex.lextable, lex.idtable);
		*log.stream << std::internal << std::setfill('-') << std::setw(48) << " ID TABLE " << std::setw(48) << "" << std::endl;
		LEX::IdTableOut(log.stream, lex.idtable);
		*log.stream << std::internal << std::setfill('-') << std::setw(48) << "IN FILE LEXEMS" << std::setw(48) << "" << std::endl;
		LEX::FullLexTable(log.stream, lex.lextable, lex.idtable);
		*log.stream << std::internal << std::setfill('-') << std::setw(48) << " SYNTAX " << std::setw(48) << "" << std::endl << std::setfill(' ');
		MFST_TRACE_START(*log.stream)
			MFST::Mfst mfst(lex, GRB::getGreibach());
		if(!mfst.start(log.stream))throw ERROR_THROW_IN(606, 0, 0);
		mfst.savededucation();
		mfst.printrules(log.stream);
		PBN::BuildCodeInPN(lex);
		*log.stream << std::internal << std::setfill('-') << std::setw(48) << "IN FILE AFTER PB" << std::setw(48) << "" << std::endl << std::setfill(' ');
		LEX::FullLexTable(log.stream, lex.lextable, lex.idtable);
		SA::SemanticsAnaliz(lex.idtable, lex.lextable);
		std::ofstream* file = CG::CreateAsmFile();
		CG::ExtrnFuncAdd(file, lex.idtable, lex.lextable);
		CG::ConstBlockFill(file, lex.idtable);
		CG::DataBLockFILL(file, lex.idtable);
		CG::CodeBlockFILL(file, lex.idtable, lex.lextable);
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
