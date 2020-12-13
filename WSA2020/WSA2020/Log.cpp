#include "Log.h"


#pragma warning(disable : 4996)

namespace Log
{
	LOG getlog(wchar_t logfile[])
	{
		LOG log;
		log.stream = new std::ofstream;
		log.stream->open(logfile);
		if (!log.stream->is_open())throw ERROR_THROW(112);
		wcscpy(log.logfile, logfile);
		return log;
	}
	void WriteLine(LOG log, const char* c, ...)
	{
		char* ptr = (char*)c;
		va_list arg;
		va_start(arg, c);

		while (ptr != "")
		{
			(*log.stream) << ptr;
			ptr = va_arg(arg, char*);
		}
		(*log.stream) << '\n';
		va_end(arg);
	}
	void WriteLine(LOG log, const wchar_t* c, ...)
	{
		va_list arg;
		va_start(arg, c);
		char* buf;
		while (c != L"")
		{
			buf = new char[wcslen(c) + 1];
			wcstombs(buf, c, wcslen(c) + 1);
			(*log.stream) << buf;
			c = va_arg(arg, const wchar_t*);
			delete[] buf;
		}
		(*log.stream) << '\n';
		va_end(arg);
	}
	void WriteLog(LOG log)
	{
		(*log.stream) << "----Протокол----- ";
		time_t realTime = time(NULL);
		tm dataTime;
		localtime_s(&dataTime, &realTime);
		if (dataTime.tm_wday < 10)(*log.stream) << '0';
		(*log.stream) << dataTime.tm_wday << ".";
		if (dataTime.tm_mday + 1 < 10)(*log.stream) << '0';
		(*log.stream) << dataTime.tm_mday + 1 << ".";
		(*log.stream) << dataTime.tm_year << " ";
		if (dataTime.tm_hour < 10)(*log.stream) << '0';
		(*log.stream) << dataTime.tm_hour << ':';
		if (dataTime.tm_min < 10)(*log.stream) << '0';
		(*log.stream) << dataTime.tm_min << ':';
		if (dataTime.tm_sec < 10)(*log.stream) << '0';
		(*log.stream) << dataTime.tm_sec << " ----------\n";
	}
	void WriteParm(LOG log, Parm::PARM parm)
	{
		char symbol; int i = 0;
		(*log.stream) << "----Параметры-----" << "\n";
		(*log.stream) << (char*)PARM_IN;
		symbol = wctob(parm.in[i]);
		while (symbol != EOF)
		{
			(*log.stream) << symbol;
			i++;
			symbol = wctob(parm.in[i]);
		}
		(*log.stream) << '\n'; i = 0;
		(*log.stream) << (char *)PARM_OUT;
		symbol = wctob(parm.out[i]);
		while (symbol != EOF)
		{
			(*log.stream) << symbol;
			i++;
			symbol = wctob(parm.out[i]);
		}
		(*log.stream) << '\n'; i = 0;
		(*log.stream) << (char* )PARM_LOG;
		symbol = wctob(parm.log[i]);
		while (symbol != EOF)
		{
			(*log.stream) << symbol;
			i++;
			symbol = wctob(parm.log[i]);
		}
		(*log.stream) << '\n';
	}
	void WriteIn(LOG log, In::IN in)
	{
		(*log.stream) << "----Исходные данные-----" << "\n";
		(*log.stream) << "Количество символов: " << in.size << '\n';
		(*log.stream) << "Проигнорировано: " << in.ignor << '\n';
		(*log.stream) << "Количество строк: " << in.lines << '\n';
	}
	void WriteError(LOG log, Error::ERROR error)
	{
		if (log.stream != NULL && log.stream->is_open())(*log.stream) << "Ошибка" <<
			error.id << ": " << error.message << "(строка:" << error.inext.line <<
			" позиция:" << error.inext.col <<")" << '\n';
		std::cout << "Ошибка " << error.id << ": " << error.message << "(строка:" << error.inext.line <<
			" позиция:" << error.inext.col << ")" << '\n';
	}
	void Close(LOG log)
	{
		log.stream->close();
		delete[] log.stream;
	}
};