#pragma once
#include <iomanip>

#include <stack>
#include "GRB.h"
#include "Lex.h"

#define  MFST_TRACE_START(log) log<<std::setw(4)<<std::left<<"Шаг"<<":"\
							      <<std::setw(20)<<std::left << " Правило"\
							      <<std::setw(30)<<std::left << " Входная лента"\
							      <<std::setw(20)<<std::left << " Стек"\
							      <<std::endl;	

#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3

template <typename T>
class Stack
{
private:
	std::stack<T> steck;
public:
	void push(T st) {
		steck.push(st);
	}
	void pop() {
		steck.pop();
	}
	T top() {
		return steck.top();
	}
	int size() {
		return steck.size();
	}
	T operator[](int s) {
		std::stack<T> st;
		st = steck;
		for (int i = (s + 1); i < steck.size(); i++)
		{
			st.pop();
		}
		return st.top();
	}
};

typedef Stack<short> MFSTSTACK;

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
		Stack<MfstState> storestate;
		Mfst();
		Mfst(
			LEX::LEX plex,
			GRB::Greibach pgreibach
		);
		char* getCSt(char* buf);
		char* getCLenta(char* buf, short pos, short n = 25);
		char* getDiagnosis(short n, char* buf);
		bool savestate(std::ofstream* out);
		bool reststate(std::ofstream* out);
		bool push_chain(
			GRB::Rule::Chain chain
		);
		RC_STEP step(std::ofstream* out);
		bool start(std::ofstream* out);
		bool savediagnosis(RC_STEP pprc_step);
		void printrules(std::ofstream* out);

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
