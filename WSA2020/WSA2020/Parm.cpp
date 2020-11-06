#include "Parm.h"


namespace Parm {

	PARM getparm(int argc, _TCHAR* argv[])
	{
		PARM parm;
		bool inFlag = false;
		bool outFlag = false;
		bool logFlag = false;
		int indexIn, indexOut, indexLog;
		for (int i = 0; i < argc; ++i)
		{
			if (wcsstr(argv[i], L"-in:"))
			{
				inFlag = true;
				indexIn = i;

			}
			else if (wcsstr(argv[i], L"-out:"))
			{
				outFlag = true;
				indexOut = i;

			}
			else if (wcsstr(argv[i], L"-log:"))
			{
				logFlag = true;
				indexLog = i;

			}
		}

		if (!inFlag)throw ERROR_THROW(100);
		if (wcslen(argv[indexIn]) > PARM_MAX_SIZE)throw ERROR_THROW(104);
		wcscpy_s(parm.in, argv[indexIn] + 4);


		if (!outFlag)
		{
			wcscpy_s(parm.out, argv[indexIn] + 4);
			wcscat_s(parm.out, PARM_OUT_DEFAULT_EXT);
		}
		else
		{
			if (wcslen(argv[indexOut]) > PARM_MAX_SIZE)throw ERROR_THROW(104);
			wcscpy_s(parm.out, argv[indexOut] + 5);
		}


		if (!logFlag)
		{
			wcscpy_s(parm.log, argv[indexIn] + 4);
			wcscat_s(parm.log, PARM_LOG_DEFAULT_EXT);
		}
		else
		{
			if (wcslen(argv[indexLog]) > PARM_MAX_SIZE)throw ERROR_THROW(104);
			wcscpy_s(parm.log, argv[indexLog] + 5);
		}
		return parm;
	}
};