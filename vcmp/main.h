
#pragma once

#include <stdio.h>
#include <windows.h>

#define MAX_PLAYER_NAME		24
#define MAX_SETTINGS_STRING 128

#define MAP_VICE			0
#define MAP_LIBERTY			1

typedef struct _GAME_SETTINGS {
	BOOL bDebug;
	BOOL bPlayOnline;
	CHAR szConnectHost[MAX_SETTINGS_STRING+1];
	CHAR szConnectPort[MAX_SETTINGS_STRING+1];
	CHAR szConnectPass[MAX_SETTINGS_STRING+1];
	CHAR szNickName[MAX_SETTINGS_STRING+1];
} GAME_SETTINGS;

#include "d3d8/include/d3d8.h"
#include "d3d8/include/d3dfont.h"
#include "d3d8/include/d3dx8tex.h"
#include "d3d8/include/DXUtil.h"

#include "game/game.h"

#include "../raknet/RakClient.h"
#include "../raknet/RakNetworkFactory.h"
#include "../raknet/BitStream.h"
#include "../raknet/PacketEnumerations.h"

#include "net/localplayer.h"
#include "gamemode/generic.h"
#include "net/netrpc.h"
#include "net/playerpool.h"
#include "net/vehiclepool.h"
#include "net/netgame.h"

#include "chatwindow.h"
#include "cmdwindow.h"

#include "game/scripting.h"

//----------------------------------------------------

void SetStringFromCommandLine(char *szCmdLine, char *szString);
void InitSettings();

//----------------------------------------------------
// EOF
