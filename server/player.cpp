
#include "netgame.h"

extern CNetGame *pNetGame;

//----------------------------------------------------

CPlayer::CPlayer()
{
	m_byteUpdateFromNetwork = UPDATE_TYPE_NONE;
	m_bytePlayerID = INVALID_PLAYER_ID;
	m_bIsActive = FALSE;
	m_bIsWasted = FALSE;
	m_byteSpectateID = INVALID_PLAYER_ID;
	m_byteVehicleID = 0;
}

//----------------------------------------------------

void CPlayer::Process()
{
	if(m_bIsActive || m_byteSpectateID != INVALID_PLAYER_ID)
	{
		if(m_byteUpdateFromNetwork != UPDATE_TYPE_NONE)
		{
			if(ValidateSyncData()) {
				BroadcastSyncData();
			}
			m_byteUpdateFromNetwork = UPDATE_TYPE_NONE;
		}
	}
}

//----------------------------------------------------
// thx CKY.BAM <g>

BOOL CPlayer::ValidateSyncData()
{
	if(m_vecPos.X > 2500.0f || m_vecPos.X < -2500.0f) {
		return FALSE;
	}
	if(m_vecPos.Y > 2500.0f || m_vecPos.Y < -2500.0f) {
		return FALSE;
	}
	if(m_vecPos.Z < -90.0f) {
		return FALSE;
	}

	return TRUE;
}

//----------------------------------------------------

void CPlayer::BroadcastSyncData()
{
	RakNet::BitStream bsSync;

	if(GetState() == PLAYER_STATE_ONFOOT && m_byteUpdateFromNetwork == UPDATE_TYPE_FULL_ONFOOT)
	{
		bsSync.Write((BYTE)ID_PLAYER_SYNC);
		bsSync.Write(m_bytePlayerID);
		bsSync.Write((PCHAR)&m_ofSync,sizeof(ONFOOT_SYNC_DATA));
		pNetGame->BroadcastData(&bsSync,HIGH_PRIORITY,UNRELIABLE,0,m_bytePlayerID);
	}
	if(GetState() == PLAYER_STATE_SPECTATING && m_byteUpdateFromNetwork == UPDATE_TYPE_SPECTATE)
	{
		bsSync.Write((BYTE)ID_AIM_SYNC);
		bsSync.Write(m_bytePlayerID);
		bsSync.Write((PCHAR)&m_ofSync,sizeof(ONFOOT_SYNC_DATA));
		bsSync.Write((PCHAR)&m_aimSync,sizeof(AIM_SYNC_DATA));
		pNetGame->BroadcastData(&bsSync,HIGH_PRIORITY,UNRELIABLE,0,m_bytePlayerID);
	}
	if(m_byteUpdateFromNetwork == UPDATE_TYPE_FULL_INCAR)
	{
		bsSync.Write((BYTE)ID_VEHICLE_SYNC);
		bsSync.Write(m_bytePlayerID);
		bsSync.Write((PCHAR)&m_icSync,sizeof(INCAR_SYNC_DATA));
		pNetGame->BroadcastData(&bsSync,HIGH_PRIORITY,UNRELIABLE,0,m_bytePlayerID);
	}
}

//----------------------------------------------------
