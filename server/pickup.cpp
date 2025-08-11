
#include "main.h"

DWORD dwPickupTime = TIME_COUNT(72000,90);

//----------------------------------------------------

CPickup::CPickup(int iType, VECTOR * vecPos, int iAmount)
{
	m_iType = iType;
	m_vecPos.X = vecPos->X;
	m_vecPos.Y = vecPos->Y;
	m_vecPos.Z = vecPos->Z;
	m_iAmount = iAmount;
	m_bIsSpawned = TRUE;
}

//----------------------------------------------------

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
		RakNet::BitStream bsPickupSpawn;

		bsPickupSpawn.Write(bytePlayerID);
		bsPickupSpawn.Write(m_iPickupID);
		bsPickupSpawn.Write(m_iType);
		bsPickupSpawn.Write(m_vecPos.X);
		bsPickupSpawn.Write(m_vecPos.Y);
		bsPickupSpawn.Write(m_vecPos.Z);
		bsPickupSpawn.Write(m_iAmount);
		bsPickupSpawn.Write(m_bIsSpawned);

		pNetGame->GetRakServer()->RPC("PickupSpawn",&bsPickupSpawn,
			HIGH_PRIORITY,RELIABLE,0,UNASSIGNED_PLAYER_ID,true,false);
	}
}

void CPickup::Process()
{
	if(!m_bIsSpawned)
	{
		if((pNetGame->GetCount() - m_dwRespawnTime) > dwPickupTime)
		{
			m_bIsSpawned = TRUE;
			SpawnForPlayer(INVALID_PLAYER_ID);
		}
	}
}
