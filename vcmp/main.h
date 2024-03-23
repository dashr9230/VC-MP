
#pragma once

#include <stdio.h>
#include <windows.h>

#define MAX_PLAYER_NAME		24
#define MAX_SETTINGS_STRING 128

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

#include "game/game.h"

#include "d3dhook/IDirect3DDevice8Hook.h"

#include "../raknet/RakNetworkFactory.h"

#include "net/localplayer.h"
#include "net/playerpool.h"
#include "net/vehiclepool.h"
#include "net/netgame.h"

#include "chatwindow.h"
#include "cmdwindow.h"
#include "scoreboard.h"
#include "netstats.h"

//----------------------------------------------------

void SetStringFromCommandLine(char *szCmdLine, char *szString);
void InitSettings();

//----------------------------------------------------
// EOF
