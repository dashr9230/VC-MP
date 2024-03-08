
#include "main.h"
#include "netgame.h"
#include "rcon.h"

void fatal_exit(char * szError);

CNetGame	*pNetGame;
CRcon		*pRcon;
CConfig		*pServerConfig;
char		*szAdminPass;
char		*szServerName;
char		*szGameMode;
int			iListenPort;
char		*szPass;
bool		szPassword;
int			iMaxPlayers;
BYTE		szMap;

//----------------------------------------------------

int main (int argc, char* argv[])
{
	int iCurrentGame=1;
	char szConfigFile[512];
	char szError[256];

	int iFriendlyFireOption;
	BYTE byteFriendlyFire=0;
	int iShowOnRadarOption;
	BYTE byteShowOnRadarOption=1;

	int iRconPort;
	int iRconMaxUsers;

	iListenPort=0;
	iMaxPlayers=0;
	szMap=MAP_NONE;

	pServerConfig = new CConfig();

	if(argc > 1) {
		strcpy(szConfigFile,argv[1]);
	} else {
		strcpy(szConfigFile,"vcmp//config.ini");
	}

	// try and read the config file.
	if(pServerConfig->ReadFile(szConfigFile) != CCONF_ERR_SUCCESS) {
		sprintf(szError,"Can't read the config file %s\n%s\n- Server Shutting Down. -",
			DEFAULT_CONFIG_FILE,pServerConfig->m_szErrorString);
		fatal_exit(szError);
	}

	#ifndef WIN32
		logprintf("Using config file: %s",szConfigFile);
	#endif

	// get the max players setting
	if((iMaxPlayers=pServerConfig->GetConfigEntryAsInt("MaxPlayers"))==(-1)) {
		iMaxPlayers = DEFAULT_MAX_PLAYERS;
	}

	if(iMaxPlayers > MAX_PLAYERS) { iMaxPlayers = MAX_PLAYERS; };

	// get the listen port setting
	if((iListenPort=pServerConfig->GetConfigEntryAsInt("ListenPort"))==(-1)) {
		iListenPort = DEFAULT_LISTEN_PORT;
	}

	// set the server pass if one is required.
	if(pServerConfig->GetConfigEntryAsBool("NeedPassword")==1) {
		szPass=pServerConfig->GetConfigEntryAsString("Password");
		szPassword=true;
	}

	// get the admin pass
	szAdminPass = pServerConfig->GetConfigEntryAsString("AdminPassword");
	if(!szAdminPass || !strlen(szAdminPass) || !strcmp(szAdminPass,"invalid")) {
		fatal_exit("I need an AdminPassword in the .ini before I can start the server.\n");
	}

	szServerName = pServerConfig->GetConfigEntryAsString("ServerName");
	if(!szServerName || !strlen(szServerName)) {
		fatal_exit("I need an Server Name in the .ini before I can start the server.\n");
	}

	szGameMode = pServerConfig->GetConfigEntryAsString("GameMode");
	if(!szGameMode || !strlen(szGameMode)) {
		fatal_exit("I need an Game Mode in the .ini before I can start the server.\n");
	}

	szMap = pServerConfig->GetConfigEntryAsInt("Map");
	if(szMap == MAP_NONE) {
		fatal_exit("I need an Game Mode in the .ini before I can start the server.\n");
	}

	// get the ff option from config (default is OFF)
	iFriendlyFireOption = pServerConfig->GetConfigEntryAsBool("FriendlyFire");
	if(iFriendlyFireOption == 1) byteFriendlyFire = 1;

	// get the show on radar option (default is ON)
	iShowOnRadarOption = pServerConfig->GetConfigEntryAsInt("ShowOnRadar");
	if(iShowOnRadarOption != -1) {
		byteShowOnRadarOption = iShowOnRadarOption;
	}

	// create the NetGame.
	pNetGame = new CNetGame(iMaxPlayers,iListenPort,0,szPass,0,byteFriendlyFire,byteShowOnRadarOption);

	if(szMap == MAP_LIBERTY) {
		printf("-- LC-MP Server Started. Port: %d Max players: %d\n** %s **\n",iListenPort,iMaxPlayers,szServerName);
	} else {
		printf("-- VC-MP Server Started. Port: %d Max players: %d\n** %s **\n",iListenPort,iMaxPlayers,szServerName);
	}

	// Get the remote console port.
	if (pServerConfig->GetConfigEntryAsInt("RconPort") == -1) {
		iRconPort = DEFAULT_RCON_PORT;
	} else {
		iRconPort = pServerConfig->GetConfigEntryAsInt("RconPort");
	}

	// Get the remote console max users.
	if (pServerConfig->GetConfigEntryAsInt("RconMaxUsers") <= 0) {
		iRconMaxUsers = DEFAULT_RCON_MAXUSERS;
	} else {
		iRconMaxUsers = pServerConfig->GetConfigEntryAsInt("RconMaxUsers");
	}

	// create rcon
	pRcon = new CRcon(iRconPort, szAdminPass, iRconMaxUsers);


	// TODO: main

	return 0;
}

//----------------------------------------------------

void fatal_exit(char * szError)
{
	#ifdef WIN32
		printf("%s\n\n",szError);
		printf("Press any key to close.");
		fgetc(stdin);
	#endif
		exit(1);
}

//----------------------------------------------------

void logprintf(char * format, ...)
{
	// nothing
}

//----------------------------------------------------
