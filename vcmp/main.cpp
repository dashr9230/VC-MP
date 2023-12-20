
#include "main.h"

CGame					*pGame=0;
DWORD					dwGameLoop=0;
DWORD					dwRenderLoop=0;
GAME_SETTINGS			tSettings;
CCmdWindow				*pCmdWindow=0;
CNetGame				*pNetGame=0;

BYTE					Map;

BOOL					bWindowedMode=FALSE;

IDirect3D8				*pD3D;
IDirect3DDevice8		*pD3DDevice;

HANDLE					hInstance;

// forwards

BOOL SubclassGameWindow();

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

			pCmdWindow = new CCmdWindow(pD3DDevice);

			// TODO: DllMain
		}
	}

	return TRUE;
}

//----------------------------------------------------

void TheGameLoop()
{
	// TODO: TheGameLoop
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
					Map = MAP_VICE;
					break;
				case 'l':
				case 'L':
					Map = MAP_LIBERTY;
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