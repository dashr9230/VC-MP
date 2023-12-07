
#include <stdio.h>
#include <windows.h>
#include "common.h"
#include "aimstuff.h"
#include "address.h"

CAMERA_AIM * pcaInternalAim = (CAMERA_AIM *)0x7E4978;
CAMERA_AIM caLocalPlayerAim;
CAMERA_AIM caRemotePlayerAim[MAX_PLAYERS];
extern BYTE * pbyteCameraMode;

BYTE byteCameraMode[MAX_PLAYERS];

//----------------------------------------------------------

void __stdcall GameSetPlayerCameraMode(BYTE byteMode, BYTE bytePlayerID)
{
	byteCameraMode[bytePlayerID] = byteMode;
}

//----------------------------------------------------------

BYTE __stdcall GameGetPlayerCameraMode(BYTE bytePlayerID)
{
	return byteCameraMode[bytePlayerID];
}

//----------------------------------------------------------

void __stdcall GameSetLocalPlayerCameraMode(BYTE byteMode)
{
	*pbyteCameraMode = byteMode;
}

//----------------------------------------------------------

BYTE __stdcall GameGetLocalPlayerCameraMode()
{
	return *pbyteCameraMode;
}

//----------------------------------------------------------

void GameAimSyncInit()
{
	memset(&caLocalPlayerAim,0,sizeof(CAMERA_AIM));
	memset(caRemotePlayerAim,0,sizeof(CAMERA_AIM) * MAX_PLAYERS);
	memset(byteCameraMode,4,MAX_PLAYERS);
}

//----------------------------------------------------------

void GameStoreLocalPlayerAim()
{
	memcpy(&caLocalPlayerAim,pcaInternalAim,sizeof(CAMERA_AIM));
}

//----------------------------------------------------------

void GameSetLocalPlayerAim()
{
	memcpy(pcaInternalAim,&caLocalPlayerAim,sizeof(CAMERA_AIM));
	//memcpy(pInternalCamera,&SavedCam,sizeof(MATRIX4X4));
}

//----------------------------------------------------------

CAMERA_AIM * GameGetInternalAim()
{
	return pcaInternalAim;
}

//----------------------------------------------------------

void GameStoreRemotePlayerAim(int iPlayer, CAMERA_AIM * caAim)
{
	memcpy(&caRemotePlayerAim[iPlayer],caAim,sizeof(CAMERA_AIM));
}

//----------------------------------------------------------

void GameSetRemotePlayerAim(int iPlayer)
{
	// backup local camera
	memcpy(pcaInternalAim,&caRemotePlayerAim[iPlayer],sizeof(CAMERA_AIM));
}

//----------------------------------------------------------
