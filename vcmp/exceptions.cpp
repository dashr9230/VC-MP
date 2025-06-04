
#include "main.h"

PCONTEXT pContextRecord;

extern   CGame * pGame;

typedef struct _CRASHDUMP_INFO
{
	DWORD dwAtAddress;
	DWORD field_4;
	//CHAR 
} CRASHDUMP_INFO;

//----------------------------------------------------

LONG WINAPI exc_handler(_EXCEPTION_POINTERS* exc_inf)
{
	pContextRecord = exc_inf->ContextRecord;

	ShowWindow(pGame->GetMainWindowHwnd(),SW_HIDE);

	// TODO: exc_handler

	//MINIDUMP_EXCEPTION_INFORMATION;

	return 1;
}

//----------------------------------------------------
