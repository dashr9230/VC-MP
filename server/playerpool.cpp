
#include "main.h"

CPlayerPool::CPlayerPool()
{
	for(BYTE bytePlayerID = 0; bytePlayerID != MAX_PLAYERS; bytePlayerID++) {
		field_0[bytePlayerID] = 0;
		field_190[bytePlayerID] = 0;
		field_C8[bytePlayerID] = 0;
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
