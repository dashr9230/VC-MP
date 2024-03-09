
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

void VCMP_SAFECALL SetPlayerPedPtrRecord(BYTE bytePlayer, DWORD dwPedPtr)
{
	dwPlayerPedPtrs[bytePlayer] = dwPedPtr;
}

//-----------------------------------------------------------

BYTE VCMP_SAFECALL FindPlayerNumFromPedPtr(DWORD dwPedPtr)
{
	BYTE x = 0;
	while(x != MAX_PLAYERS)	{
		if(dwPlayerPedPtrs[x] == dwPedPtr) return x;
		x++;
	}
	return 0;
}

//-----------------------------------------------------------
