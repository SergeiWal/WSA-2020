#pragma once
#include <iomanip>

#include <stack>
#include "GRB.h"
#include "Lex.h"

#define  MFST_TRACE_START std::cout<<std::setw(4)<<std::left<<"Шаг"<<":"\
							      <<std::setw(20)<<std::left << " Правило"\
							      <<std::setw(30)<<std::left << " Входная лента"\
							      <<std::setw(20)<<std::left << " Стек"\
							      <<std::endl;	

#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3



typedef std::stack<short> MFSTSTACK;
namespace MFST
{
	struct MfstState
	{
		short lenta_position;
		short nrule;
		short nrulechain;
		MFSTSTACK st;
		MfstState();
		MfstState(
			short pposition,
			MFSTSTACK pst,
			short pnrulechain
		);
		MfstState(
			short pposition,
			MFSTSTACK pst,
			short pnrule,
			short pnrulechain
		);
	};

	struct Mfst
	{
		enum RC_STEP
		{
			NS_OK,
			NS_NORULE,
			NS_NORULECHAIN,
			NS_ERROR,
			TS_OK,
			TS_NOK,
			LENTA_END,
			SURPRISE
		};
		struct MfstDiagnosis
		{
			short lenta_position;
			RC_STEP rc_step;
			short nrule;
			short nrule_chain;
			MfstDiagnosis();
			MfstDiagnosis(
				short plenta_position,
				RC_STEP prc_step,
				short pnrule,
				short pnrule_chain
			); 
		} diagnosis[MFST_DIAGN_NUMBER];

		GRBALPHABET* lenta;
		short lenta_position;
		short nrule;
		short nrulechain;
		short lenta_size;
		GRB::Greibach greibach;
		LEX::LEX lex;
		MFSTSTACK st;
		std::stack<MfstState> storestate;
		Mfst();
		Mfst(
			LEX::LEX plex,
			GRB::Greibach pgreibach
		);
		char* getCSt(char* buf);
		char* getCLenta(char* buf, short pos, short n = 25);
		char* getDiagnosis(short n, char* buf);
		bool savestate();
		bool reststate();
		bool push_chain(
			GRB::Rule::Chain chain
		);
		RC_STEP step();
		bool start();
		bool savediagnosis(RC_STEP pprc_step);
		void printrules();

		struct Deducation
		{
			short size;
			short* nrules;
			short* nruleschains;
			Deducation() { size = 0; nrules = 0; nruleschains = 0; }
		}deducation;
		bool savededucation();
	};
};
