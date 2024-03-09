
#include "main.h"

BYTE					byteMapType;

CGame					*pGame=0;
DWORD					dwGameLoop=0;
DWORD					dwRenderLoop=0;
GAME_SETTINGS			tSettings;

BOOL					bWindowedMode=FALSE;

HANDLE					hInstance;

// forwards

void TheGameLoop();
void TheRenderLoop();

//----------------------------------------------------

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if(DLL_PROCESS_ATTACH==fdwReason)
	{
		hInstance = hinstDLL;

		InitSettings();

		if(tSettings.bDebug || tSettings.bPlayOnline) {

			dwGameLoop = (DWORD)TheGameLoop;
			dwRenderLoop = (DWORD)TheRenderLoop;

			pGame = new CGame();
			pGame->StartGame();
		}
		// else they must want to play single
		// player or they got the command line
		// arguments wrong.
	}

	return TRUE;
}

//----------------------------------------------------
// Main loop which is called before game processing.
// This is actually a result of a hook inside GTA's
// main loop (TheGameLoop())

void TheGameLoop()
{
	// TODO: TheGameLoop()
}

//----------------------------------------------------

void TheRenderLoop()
{

}

//----------------------------------------------------

void InitSettings()
{
	PCHAR szCmdLine = GetCommandLine();

	memset(&tSettings,0,sizeof(GAME_SETTINGS));

	while(*szCmdLine) {

		if(*szCmdLine == '-' || *szCmdLine == '/') {
			szCmdLine++;
			switch(*szCmdLine) {
				case 'v':
				case 'V':
					byteMapType = MAP_VICE;
					break;
				case 'l':
				case 'L':
					byteMapType = MAP_LIBERTY;
					break;
				case 'd':
				case 'D':
					tSettings.bDebug = TRUE;
					tSettings.bPlayOnline = FALSE;
					break;
				case 'c':
				case 'C':
					tSettings.bPlayOnline = TRUE;
					tSettings.bDebug = FALSE;
					break;
				case 'w':
				case 'W':
					bWindowedMode = TRUE;
					break;
				case 'h':
				case 'H':
					szCmdLine++;
					SetStringFromCommandLine(szCmdLine,tSettings.szConnectHost);
					break;
				case 'p':
				case 'P':
					szCmdLine++;
					SetStringFromCommandLine(szCmdLine,tSettings.szConnectPort);
					break;
				case 'n':
				case 'N':
					szCmdLine++;
					SetStringFromCommandLine(szCmdLine,tSettings.szNickName);
					break;
				case 'z':
				case 'Z':
					szCmdLine++;
					SetStringFromCommandLine(szCmdLine,tSettings.szConnectPass);
					break;
			}
		}

		szCmdLine++;
	}
}

//----------------------------------------------------

void SetStringFromCommandLine(char *szCmdLine, char *szString)
{
	while(*szCmdLine == ' ') szCmdLine++;
	while(*szCmdLine &&
		  *szCmdLine != ' ' &&
		  *szCmdLine != '-' &&
		  *szCmdLine != '/')
	{
		*szString = *szCmdLine;
		szString++; szCmdLine++;
	}
	*szString = '\0';
}

//----------------------------------------------------
