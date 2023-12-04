
#include "main.h"

extern CNetGame *pNetGame;

DWORD dwPickupTime = _cst(90,800);

void CPickup::Process()
{
	if(!field_18 && (pNetGame->GetCount() - field_1C) > dwPickupTime)
	{
		field_18 = 1;
		SpawnForPlayer(INVALID_PLAYER_ID);
	}
}

BOOL CPickup::ValidateSyncData()
{
	if(m_vecPos.X > 2500.0f || m_vecPos.X < -2500.0f) {
		return FALSE;
	}
	if(m_vecPos.Y > 2500.0f || m_vecPos.Y < -2500.0f) {
		return FALSE;
	}
	if(m_vecPos.Z > 50000.0f || m_vecPos.Z  < -90.0f) {
		return FALSE;
	}

	return TRUE;
}

void CPickup::SpawnForPlayer(BYTE bytePlayerID)
{
	if(ValidateSyncData()) {
		// TODO: CPickup::SpawnForPlayer
	}
}
