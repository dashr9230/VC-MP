
#include "main.h"

void CPlayer::Process()
{
	if(m_bIsActive || field_5 != -1)
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

BOOL CPlayer::ValidateSyncData()
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

void CPlayer::BroadcastSyncData()
{
	// TODO: CPlayer::BroadcastSyncData
}
