
#ifndef VCMPSRV_MAIN_H
#define VCMPSRV_MAIN_H

// -------
// DEFINES
// -------

#define MAX_PLAYERS				50
#define MAX_VEHICLES			200

#define DEFAULT_MAX_PLAYERS		50
#define DEFAULT_LISTEN_PORT		8192
#define DEFAULT_RCON_PORT		8190
#define DEFAULT_RCON_MAXUSERS	8

// ------------
// VERSION INFO
// ------------

#define VCMP_VERSION "0.3r2"

// ------------
// OS SPECIFICS
// ------------

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#define SLEEP(x) { Sleep(x); }

	#include <windows.h>
#else
	#define SLEEP(x) { usleep(x * 1000); }

	#include <unistd.h>
#endif

// --------
// INCLUDES
// --------

// Regular crap
#include <stdio.h>

// Std
#include <map>
#include <string>

// RakNet
#include "../raknet/RakServer.h"
#include "../raknet/RakNetworkFactory.h"

// VC:MP

#include "system.h"
#include "console.h"
#include "scrtimers.h"
#include "gamemodes.h"
#include "filterscripts.h"
#include "netrpc.h"
#include "playerpool.h"
#include "vehiclepool.h"
#include "pickuppool.h"
#include "netgame.h"
#include "rcon.h"

// ---------
// EXTERNALS
// ---------

extern CConsole* pConsole;
extern CNetGame* pNetGame;

// -------------------
// FUNCTION PROTOTYPES
// -------------------

void logprintf(char* format, ...);
void flogprintf(char* format, ...);

#ifdef LINUX
char* strlwr(char* str);
#endif

#endif // VCMPSRV_MAIN_H
