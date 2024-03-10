
#include <windows.h>
#include <stdio.h>
#include "game.h"
#include "../main.h"

DWORD dwPlayerPedPtrs[MAX_PLAYERS];

#define VCMP_SAFECALL __stdcall

//-----------------------------------------------------------

void VCMP_SAFECALL GameDisableCheatCodes()
{
	DWORD p1,p2;
	VirtualProtect((void*)0x602BDC,16,PAGE_EXECUTE_READWRITE,&p1);
	*(BYTE *)0x602BDC = 0x90;
	memset((void*)0x602BE7,0x90,5);
	VirtualProtect((void*)0x602BDC,16,p1,&p2);
}

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
