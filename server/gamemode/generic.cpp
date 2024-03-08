
#include "../netgame.h"

extern CNetGame *pNetGame;
extern CConfig *pServerConfig;

//----------------------------------------------------
// RETURNS NUMBER OF SPAWNS

int CGameModeGeneric::Init()
{
	// Load up all the spawns.
	int iSpawnConfigCount = pServerConfig->GetConfigArrayCount("CLASS");
	int x=1;
	char * szSpawnConf;

	while(x<=iSpawnConfigCount) {
		szSpawnConf = pServerConfig->GetConfigEntryAsString("CLASS",x);
		if(szSpawnConf != NULL) {
			// TODO: CGameModeGeneric::Init
		}
		x++;
	}

	return iSpawnConfigCount;
}

//----------------------------------------------------

int CGameModeGeneric::InitAmmu()
{
	// TODO: CGameModeGeneric::InitAmmu
	return 0;
}

//----------------------------------------------------

void CGameModeGeneric::HandleClientJoin(BYTE bytePlayerID)
{
	// nothing
}

//----------------------------------------------------

BOOL CGameModeGeneric::HandleSpawnClassRequest(BYTE bytePlayerID,
											   int iSpawnType)
{
	CPlayer *pPlayer;
	pPlayer = pNetGame->GetPlayerPool()->GetAt(bytePlayerID);

	// TODO: CGameModeGeneric::HandleSpawnClassRequest
	return FALSE;
}

//----------------------------------------------------
// EOF
