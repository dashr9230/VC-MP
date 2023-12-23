
#include "../main.h"

extern CNetGame* pNetGame;

BYTE byte_100F73E0;

//----------------------------------------------------------

CGameModeGeneric::CGameModeGeneric()
{
	field_E = 0;
	byte_100F73E0 = 0;
	field_F = GetTickCount();
	field_13 = GetTickCount();
	HandleClassSelection(pNetGame->GetPlayerPool()->GetLocalPlayer());
	sub_10022A50();
}

//----------------------------------------------------------

void CGameModeGeneric::HandleClassSelection(CLocalPlayer *pLocalPlayer)
{
	// TODO: CGameModeGeneric::HandleClassSelection
}

//----------------------------------------------------------

void CGameModeGeneric::sub_10022A50()
{
	// TODO: CGameModeGeneric::sub_10022A50()
}