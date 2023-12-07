
#include <stdio.h>
#include <windows.h>
#include "common.h"
#include "keystuff.h"
#include "address.h"

//-----------------------------------------------------------

GTA_CONTROLSET *pGcsInternalKeys = (GTA_CONTROLSET *)ADDR_KEYSTATES;
GTA_CONTROLSET GcsLocalPlayerKeys;
GTA_CONTROLSET GcsRemotePlayerKeys[MAX_PLAYERS];

BYTE	byteSaveDriveByLeft;
BYTE	byteSaveDriveByRight;
BYTE   *pbyteDriveByLeft =  (BYTE *)0x7E4818;
BYTE   *pbyteDriveByRight = (BYTE *)0x7E4819;

//-----------------------------------------------------------

void GameKeyStatesInit()
{
	int x=0;
	memset(&GcsLocalPlayerKeys,0,sizeof(GTA_CONTROLSET));
	while(x!=MAX_PLAYERS) {
		memset(&GcsRemotePlayerKeys[x],0,sizeof(GTA_CONTROLSET));
		x++;
	}
}

//-----------------------------------------------------------

void GameStoreLocalPlayerKeys()
{
	memcpy(&GcsLocalPlayerKeys,pGcsInternalKeys,sizeof(GTA_CONTROLSET));

	// save current driveby state
	byteSaveDriveByLeft = *pbyteDriveByLeft;
	byteSaveDriveByRight = *pbyteDriveByRight;
}

//-----------------------------------------------------------

void GameSetLocalPlayerKeys()
{
	memcpy(pGcsInternalKeys,&GcsLocalPlayerKeys,sizeof(GTA_CONTROLSET));

	// restore the driveby state also
	*pbyteDriveByLeft = byteSaveDriveByLeft;
	*pbyteDriveByRight = byteSaveDriveByRight;
}

//-----------------------------------------------------------

void GameStoreRemotePlayerKeys(int iPlayer, GTA_CONTROLSET * pGcsKeyStates)
{
	memcpy(&GcsRemotePlayerKeys[iPlayer],pGcsKeyStates,sizeof(GTA_CONTROLSET));
}

//-----------------------------------------------------------

GTA_CONTROLSET * GameGetInternalKeys()
{
	return pGcsInternalKeys;
}

//-----------------------------------------------------------

GTA_CONTROLSET * GameGetLocalPlayerKeys()
{
	return &GcsLocalPlayerKeys;
}

//-----------------------------------------------------------

GTA_CONTROLSET * GameGetPlayerKeys(int iPlayer)
{
	return &GcsRemotePlayerKeys[iPlayer];
}

//-----------------------------------------------------------

void GameResetPlayerKeys(int iPlayer)
{
	memset(&GcsRemotePlayerKeys[iPlayer],0,sizeof(GTA_CONTROLSET));
}

//-----------------------------------------------------------

void GameResetLocalKeys()
{
	memset(pGcsInternalKeys,0,80);
}

//-----------------------------------------------------------