
#include "../main.h"
#include "util.h"

//-----------------------------------------------------------

// Obtain an instance of CPlayerPed for the local player.

CPlayerPed::CPlayerPed()
{
	m_dwGTAId = 1; // 0x001
	m_pPed = GamePool_FindPlayerPed();
	field_8 = 0;
	field_D = 0;
}

//-----------------------------------------------------------
