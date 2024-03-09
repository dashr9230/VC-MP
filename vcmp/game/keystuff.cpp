
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

void GameSetRemotePlayerKeys(int iPlayer)
{
	memcpy(pGcsInternalKeys,&GcsRemotePlayerKeys[iPlayer],sizeof(GTA_CONTROLSET));

	if(GcsRemotePlayerKeys[iPlayer].wKeys1[KEY_INCAR_LOOKL]) {
		*pbyteDriveByLeft = 1;
	} else {
		*pbyteDriveByLeft = 0;
	}

	if(GcsRemotePlayerKeys[iPlayer].wKeys1[KEY_INCAR_LOOKR]) {
		*pbyteDriveByRight = 1;
	} else {
		*pbyteDriveByRight = 0;
	}
}

//-----------------------------------------------------------

GTA_CONTROLSET * GameGetInternalKeys()
{
	return pGcsInternalKeys;
}

//-----------------------------------------------------------

GTA_CONTROLSET * GameGetPlayerKeys(int iPlayer)
{
	return &GcsRemotePlayerKeys[iPlayer];
}

//-----------------------------------------------------------



