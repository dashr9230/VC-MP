
#include "main.h"

CPlayerPool::CPlayerPool()
{
	for(BYTE bytePlayerID = 0; bytePlayerID != MAX_PLAYERS; bytePlayerID++) {
		m_bPlayerSlotState[bytePlayerID] = FALSE;
		field_190[bytePlayerID] = 0;
		m_pPlayers[bytePlayerID] = NULL;
	}
}

CPlayerPool::~CPlayerPool()
{
	for(BYTE bytePlayerID = 0; bytePlayerID != MAX_PLAYERS; bytePlayerID++) {
		Delete(bytePlayerID,0);
	}
}

BOOL CPlayerPool::Delete(BYTE bytePlayerID, BYTE byteReason)
{
	// TODO: CPlayerPool::Delete

	return FALSE;
}

void CPlayerPool::Process()
{
	BYTE bytePlayerID = 0;

	while(bytePlayerID != MAX_PLAYERS) {
		if(TRUE == m_bPlayerSlotState[bytePlayerID]) {
			m_pPlayers[bytePlayerID]->Process();
		}
		bytePlayerID++;
	}
}

