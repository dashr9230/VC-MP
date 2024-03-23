
#include "main.h"

BYTE					byteMapType;

CGame					*pGame=0;
DWORD					dwGameLoop=0;
DWORD					dwRenderLoop=0;
GAME_SETTINGS			tSettings;
CChatWindow				*pChatWindow=0;
CCmdWindow				*pCmdWindow=0;

BOOL					bWindowedMode=FALSE;

IDirect3D8				*pD3D;
IDirect3DDevice8		*pD3DDevice;
IDirect3DDevice8Hook	*pD3DDeviceHook;

HANDLE					hInstance;
CScoreBoard				*pScoreBoard;
CNetStats				*pNetStats;

// forwards

BOOL SubclassGameWindow();
void SetupCommands();

void TheGameLoop();
void TheRenderLoop();

int DetermineGTAVersion();

#define UNKNOWN_VERSION	0
#define VICE_10			1
#define VICE_11			2

//----------------------------------------------------

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if(DLL_PROCESS_ATTACH==fdwReason)
	{
		hInstance = hinstDLL;

		InitSettings();

		if(tSettings.bDebug || tSettings.bPlayOnline) {

			// Check the GTA version
			if(DetermineGTAVersion() != VICE_10) {
				MessageBox(0,"Incorrect gta-vc.exe version detected.\nYou must use GTA:VC 1.0 to play VC:MP","VC:MP Error",MB_OK);
				SetForegroundWindow(HWND_DESKTOP);
				ExitProcess(1);
			}

			dwGameLoop = (DWORD)TheGameLoop;
			dwRenderLoop = (DWORD)TheRenderLoop;

			pGame = new CGame();
			pGame->StartGame();

			SubclassGameWindow();

			// Time to hook directx...

			// Grab the real IDirect3D8 * from the game.
			pD3D = (IDirect3D8 *)pGame->GetD3D();

			// Grab the real IDirect3DDevice8 * from the game.
			pD3DDevice = (IDirect3DDevice8 *)pGame->GetD3DDevice();

			// Create instances of our hook classes and force GTA to
			// chew on them.
			pD3DDeviceHook = new IDirect3DDevice8Hook;

			pGame->SetD3DDevice((DWORD)pD3DDeviceHook);

			// Create instances of the chat and input classes.
			pChatWindow = new CChatWindow(pD3DDevice);
			pCmdWindow = new CCmdWindow(pD3DDevice);

			pScoreBoard = new CScoreBoard();
			pNetStats = new CNetStats();

			SetupCommands();
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

int DetermineGTAVersion()
{
	BYTE* VerCheck = (BYTE*)0x608578;

	switch (*VerCheck)
	{
	case 0x81: 
		return VICE_11;
	case 0x5D: 
		return VICE_10;
	}
	return UNKNOWN_VERSION;
}

//----------------------------------------------------
