
#include "main.h"

PCONTEXT pContextRecord;
extern   CGame * pGame;

//----------------------------------------------------

LONG WINAPI exc_handler(_EXCEPTION_POINTERS* exc_inf)
{
	pContextRecord = exc_inf->ContextRecord;

	ShowWindow(pGame->GetMainWindowHwnd(),SW_HIDE);

	// TODO: exc_handler

	return EXCEPTION_CONTINUE_SEARCH;
}

//----------------------------------------------------
