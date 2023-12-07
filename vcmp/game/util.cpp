
#include <windows.h>
#include <stdio.h>
#include "game.h"
#include "../main.h"

DWORD dwPlayerPedPtrs[MAX_PLAYERS];

#define VCMP_SAFECALL __stdcall

//-----------------------------------------------------------

void VCMP_SAFECALL InitPlayerPedPtrRecords() 
{
	memset(&dwPlayerPedPtrs[0],0,sizeof(DWORD) * MAX_PLAYERS);
}

//-----------------------------------------------------------
