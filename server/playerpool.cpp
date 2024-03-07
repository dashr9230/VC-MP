
#include "netgame.h"

//----------------------------------------------------

CPlayerPool::CPlayerPool()
{
	BYTE bytePlayerID = 0;
	while(bytePlayerID != MAX_PLAYERS) {
		field_0[bytePlayerID] = 0;
		field_190[bytePlayerID] = 0;
		bytePlayerID++;
	}
}

//----------------------------------------------------
