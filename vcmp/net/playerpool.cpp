
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
