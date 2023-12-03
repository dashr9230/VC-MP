
#include "main.h"

CNetGame	*pNetGame	= NULL;
CConsole	*pConsole	= NULL;
CRcon		*pRcon		= NULL;

char *szAdminPass;

int			iListenPort;
int			iMaxPlayers;
BYTE		szMap;
bool		bFriendyFire;

FILE		*pLogFile;
bool		bQuitApp = false;
BOOL		bGameModeFinished=FALSE;

//----------------------------------------------------

#ifdef WIN32
HANDLE hConsoleExecuteEvent;
DWORD WINAPI ConsoleInputThread(void* pParam)
{
	char buf[512];
	while (true)
	{
		DWORD dwRead;
		ReadConsole(GetStdHandle(STD_INPUT_HANDLE), buf, 255, &dwRead, NULL);
		if (dwRead > 2)
		{
			buf[dwRead-2] = 0;
			WaitForSingleObject(hConsoleExecuteEvent, INFINITE);
			pConsole->Execute(buf);
			SetEvent(hConsoleExecuteEvent);
		}
	}
}

//----------------------------------------------------

BOOL WINAPI CtrlHandler(DWORD type)
{
	switch (type)
	{
		case CTRL_C_EVENT:
		case CTRL_BREAK_EVENT:
		case CTRL_CLOSE_EVENT:
		case CTRL_LOGOFF_EVENT:
		case CTRL_SHUTDOWN_EVENT:
			bQuitApp = true;
			return TRUE;
	}
	return FALSE;
}

#endif

//----------------------------------------------------

void ServerPasswordChanged()
{
	if (pNetGame)
	{
		char* szPass = pConsole->GetStringVariable("password");
		if ((szPass) && (szPass[0] != 0) && (szPass[0] != '0'))
		{
			logprintf("Setting server password to: \"%s\"", szPass);
			pNetGame->GetRakServer()->SetPassword(szPass);
		} else {
			logprintf("Server password has been removed.");
			pNetGame->GetRakServer()->SetPassword(NULL);
		}
	}
}

//----------------------------------------------------

void ServerMaxPlayersChanged()
{
	int maxplayers = pConsole->GetIntVariable("maxplayers");
	if (maxplayers < 0)
		pConsole->SetIntVariable("maxplayers", 0);
	if (maxplayers > MAX_PLAYERS)
		pConsole->SetIntVariable("maxplayers", MAX_PLAYERS);

	if (pNetGame)
	{
		if (pConsole->GetIntVariable("maxplayers") > MAX_PLAYERS) {
			pConsole->SetIntVariable("maxplayers", MAX_PLAYERS);
		}
		pNetGame->GetRakServer()->SetAllowedPlayers((WORD)pConsole->GetIntVariable("maxplayers"));
	}
}

//----------------------------------------------------

#ifdef LINUX

// strlwr is not included with the GNU C lib it seems.
char* strlwr(char* str)
{
	for (size_t i=0; i<strlen(str); i++)
	{
		if ((str[i] >= 'A') && (str[i] <= 'Z'))
		{
			str[i] -= 32;
		}
	}
	return str;
}

#endif	// #ifdef LINUX

//----------------------------------------------------

int main (int argc, char** argv)
{
	iMaxPlayers	= DEFAULT_MAX_PLAYERS;
	iListenPort	= DEFAULT_LISTEN_PORT;
	int iRconPort = DEFAULT_RCON_PORT;
	int iRconMaxUsers = DEFAULT_RCON_MAXUSERS;
	int iLanMode = 0;
	szMap = 1;
	BYTE byteFriendlyFire=0;

	// Open the log file
	pLogFile = fopen("server_log.txt", "w");

	// Write welcome message.
	logprintf("");
	logprintf(" VC:MP Dedicated Server");
	logprintf(" ----------------------");
	logprintf(" v" VCMP_VERSION ", ¬2005-2010 VC:MP Team\n");

	// Create the Console
	pConsole = new CConsole();

	pConsole->AddVariable("maxplayers", CON_VARTYPE_INT, 0, &iMaxPlayers, ServerMaxPlayersChanged);
	pConsole->AddVariable("port", CON_VARTYPE_INT, 0, &iListenPort);
	pConsole->AddVariable("friendlyfire", CON_VARTYPE_INT, 0, &byteFriendlyFire);
	bFriendyFire = byteFriendlyFire;
	pConsole->AddVariable("lanmode", CON_VARTYPE_INT, 0, &iLanMode);
	pConsole->AddStringVariable("password", 0, NULL, ServerPasswordChanged);
	pConsole->AddStringVariable("hostname", 0, "VC:MP Server");
	pConsole->AddStringVariable("mapname", 0, "Vice-City");
	pConsole->AddStringVariable("weburl", CON_VARFLAG_RULE, "www.vicecitymultiplayer.com");
	pConsole->AddStringVariable("rcon_password", 0, "INVALID");
	pConsole->AddStringVariable("gamemodetext", 0, "Unknown");
	pConsole->AddStringVariable("filterscripts", 0, "");
	pConsole->AddVariable("rcon_max_users", CON_VARTYPE_INT, 0, &iRconMaxUsers);
	pConsole->AddVariable("rcon_port", CON_VARTYPE_INT, 0, &iRconPort);

	// Add 16 gamemode variables.
	int x=0;
	char t[64];
	while(x!=16) {
		sprintf(t,"gamemode%u",x);
		pConsole->AddStringVariable(t,0,"");
		x++;
	}

	// Exec the server config!
	pConsole->Execute("exec server");

	// Change some var flags to read-only (can only be accessed from server.cfg).
	pConsole->ModifyVariableFlags("port", CON_VARFLAG_READONLY);
	pConsole->ModifyVariableFlags("filterscripts", CON_VARFLAG_READONLY);

#ifdef WIN32
	SetConsoleCtrlHandler(CtrlHandler, TRUE);
	hConsoleExecuteEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	DWORD dwThreadId;
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ConsoleInputThread, NULL, 0, &dwThreadId);
#endif

	// Create the NetGame.
	pNetGame = new CNetGame();
	pNetGame->Init();

	// create rcon
	pRcon = new CRcon(iRconPort,
					  pConsole->GetStringVariable("rcon_password"),
					  iRconMaxUsers);
	if(pRcon) {
		printf("** rcon server started on port %d - password: %s - max users: %d\n",
			iRconPort, pConsole->GetStringVariable("rcon_password"), iRconMaxUsers);
	}

	// While the app is running...
	while (!bQuitApp)
	{
		pNetGame->Process();
		pRcon->Process();

		if(TRUE == bGameModeFinished) {
			pNetGame->ShutdownForGameModeRestart();
			bGameModeFinished = FALSE;
		}

		#ifdef WIN32
			SetEvent(hConsoleExecuteEvent);
			WaitForSingleObject(hConsoleExecuteEvent, INFINITE);
		#endif

		SLEEP(5);
	}

	delete pNetGame;

	// If WIN32: Kill the input thread.
	#ifdef WIN32
		TerminateThread(hThread, 0);
		CloseHandle(hConsoleExecuteEvent);
	#endif

	delete pConsole;

	delete pRcon;

	fclose(pLogFile);

	return 0;
}

//----------------------------------------------------

void logprintf(char* format, ...)
{
	va_list ap;
	va_start(ap, format);

	char buffer[512];
	vsprintf(buffer, format, ap);

	va_end(ap);

#ifdef WIN32
	puts(buffer);
#endif

	fprintf(pLogFile, "%s\n", buffer);
}

//----------------------------------------------------

// Print to log file only.
void flogprintf(char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	vfprintf(pLogFile, format, ap);
	va_end(ap);
}

//----------------------------------------------------
