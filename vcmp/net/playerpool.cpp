
#include "../main.h"

//----------------------------------------------------

CPlayerPool::CPlayerPool()
{
	BYTE bytePlayerID = 0;

	m_pLocalPlayer = new CLocalPlayer();

	while(bytePlayerID < MAX_PLAYERS) {
		field_0[bytePlayerID] = 0;
		field_CD[bytePlayerID] = 0;
		bytePlayerID++;
	}
}

//----------------------------------------------------

CPlayerPool::~CPlayerPool()
{
	BYTE bytePlayerID = 0;

	delete m_pLocalPlayer;

	while(bytePlayerID < MAX_PLAYERS) {
		Delete(bytePlayerID,0);
		bytePlayerID++;
	}
}

//----------------------------------------------------

BOOL CPlayerPool::Delete(BYTE bytePlayerID, BYTE byteReason)
{
	// TODO: CPlayerPool::Delete

	return TRUE;
}

//----------------------------------------------------
