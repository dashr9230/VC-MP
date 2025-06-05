
#include "../main.h"
#include "game.h"
#include "util.h"

//-----------------------------------------------------------

//-----------------------------------------------------------
// Obtain an instance of CPlayerPed for the local player.

CPlayerPed::CPlayerPed()
{
	field_4 = 1;
	m_pPed = GamePool_FindPlayerPed();
	field_8 = 0;
	field_D = 0;
	field_11 = 0;
	field_12 = 1;
}

//-----------------------------------------------------------

void SetDrivebyState(int iToggle)
{
	if(GamePool_Ped_GetAt(m_dwGTAId) == 0) return;
	m_iDriveByState = iToggle;
	ScriptCommand(&set_driveby_state, m_bytePlayerNumber, iToggle != 0);
}
