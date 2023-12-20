
#include "../main.h"
#include "game.h"
#include "util.h"

//-----------------------------------------------------------
// Obtain an instance of CPlayerPed for the local player.

CPlayerPed::CPlayerPed()
{
	m_dwGTAId = 1; // 0x001
	m_pPed = GamePool_FindPlayerPed();
	m_bytePlayerNumber = 0;
	field_D = 0;
	field_11 = 0;
	field_12 = 1;
}

//-----------------------------------------------------------

void CPlayerPed::sub_1000B660(int a2)
{
	if(GamePool_Ped_GetAt(m_dwGTAId) == 0) return;
	field_1A = a2;
	ScriptCommand(&set_player_drive_by_mode,m_bytePlayerNumber,a2!=0);
}

//-----------------------------------------------------------