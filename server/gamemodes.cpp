
#include "main.h"

#define CHECK_INIT() { if (!m_bInitialised) return 0; };

extern "C" int amx_CoreInit(AMX* amx);
extern "C" int amx_CoreCleanup(AMX* amx);
extern "C" int amx_FloatInit(AMX* amx);
extern "C" int amx_FloatCleanup(AMX* amx);
extern "C" int amx_StringInit(AMX* amx);
extern "C" int amx_StringCleanup(AMX* amx);
extern "C" int amx_FileInit(AMX* amx);
extern "C" int amx_FileCleanup(AMX* amx);
extern "C" int amx_TimeInit(AMX* amx);
extern "C" int amx_TimeCleanup(AMX* amx);
extern "C" int amx_DGramInit(AMX* amx);
extern "C" int amx_DGramCleanup(AMX* amx);

int AMXAPI aux_LoadProgram(AMX* amx, char* filename);
int AMXAPI aux_FreeProgram(AMX *amx);
char * AMXAPI aux_StrError(int errnum);
void AMXPrintError(CGameMode* pGameMode, AMX *amx, int error);
int amx_CustomInit(AMX *amx);

char szGameModeFileName[256];

//----------------------------------------------------------------------------------

CGameMode::CGameMode()
{
	m_bInitialised = false;
	m_bSleeping = false;
	m_pScriptTimers = new CScriptTimers;
}

//----------------------------------------------------------------------------------

CGameMode::~CGameMode()
{
	Unload();
	SAFE_DELETE(m_pScriptTimers);
}

//----------------------------------------------------------------------------------

bool CGameMode::Load(char* pFileName)
{
	if (m_bInitialised)
		Unload();

	FILE* f = fopen(pFileName, "rb");
	if (!f) return false;
	fclose(f);

	memset((void*)&m_amx, 0, sizeof(AMX));
	m_fSleepTime = 0.0f;
	strcpy(szGameModeFileName, pFileName);

	int err = aux_LoadProgram(&m_amx, szGameModeFileName);
	if (err != AMX_ERR_NONE)
	{
		AMXPrintError(this, &m_amx, err);
		logprintf("Failed to load '%s' script.", szGameModeFileName);
		return false;
	}

	amx_CoreInit(&m_amx);
	amx_FloatInit(&m_amx);
	amx_StringInit(&m_amx);
	amx_FileInit(&m_amx);
	amx_TimeInit(&m_amx);
	amx_DGramInit(&m_amx);
	amx_CustomInit(&m_amx);

	m_bInitialised = true;

	// Execute OnGameModeInit callback, if it exists!
	int tmp;
	if (!amx_FindPublic(&m_amx, "OnGameModeInit", &tmp))
		amx_Exec(&m_amx, (cell*)&tmp, tmp);
	// ----------------------------------------------

	cell ret = 0;
	err = amx_Exec(&m_amx, &ret, AMX_EXEC_MAIN);
	if (err == AMX_ERR_SLEEP)
	{
		m_bSleeping = true;
		m_fSleepTime = ((float)ret / 1000.0f);
	}
	else if (err != AMX_ERR_NONE)
	{
		m_bSleeping = false;
		AMXPrintError(this, &m_amx, err);
	}

	return true;
}

//----------------------------------------------------------------------------------

void CGameMode::Unload()
{
	// Execute OnGameModeExit callback, if it exists!
	int tmp;
	if (!amx_FindPublic(&m_amx, "OnGameModeExit", &tmp))
		amx_Exec(&m_amx, (cell*)&tmp, tmp);
	// ----------------------------------------------

	if (m_bInitialised)
	{
		aux_FreeProgram(&m_amx);
		amx_DGramCleanup(&m_amx);
		amx_TimeCleanup(&m_amx);
		amx_FileCleanup(&m_amx);
		amx_StringCleanup(&m_amx);
		amx_FloatCleanup(&m_amx);
		amx_CoreCleanup(&m_amx);
	}
	m_bInitialised = false;
	m_bSleeping = false;
}

//----------------------------------------------------------------------------------

void CGameMode::Frame(float fElapsedTime)
{
	if (!m_bInitialised)
		return;

	if (m_pScriptTimers)
		m_pScriptTimers->Process((DWORD)(fElapsedTime * 1000.0f));

	if (!m_bSleeping)
		return;

	if (m_fSleepTime > 0.0f)
	{
		m_fSleepTime -= fElapsedTime;
	}
	else
	{
		cell ret;
		int err = amx_Exec(&m_amx, &ret, AMX_EXEC_CONT);
		if (err == AMX_ERR_SLEEP)
		{
			m_bSleeping = true;
			m_fSleepTime = ((float)ret / 1000.0f);
		}
		else
		{
			m_bSleeping = false;
			AMXPrintError(this, &m_amx, err);
		}
	}
}

//----------------------------------------------------------------------------------

int CGameMode::CallPublic(char* szFuncName)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, szFuncName, &idx))
		amx_Exec(&m_amx, &ret, idx);
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerConnect(playerid);
int CGameMode::OnPlayerConnect(cell playerid)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, "OnPlayerConnect", &idx))
	{
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

int CGameMode::OnPlayerVersion(cell playerid, cell version)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, "OnPlayerVersion", &idx))
	{
		amx_Push(&m_amx, version);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerDisconnect(playerid, reason);
int CGameMode::OnPlayerDisconnect(cell playerid, cell reason)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, "OnPlayerDisconnect", &idx))
	{
		amx_Push(&m_amx, reason);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerSpawn(playerid, classid);
int CGameMode::OnPlayerSpawn(cell playerid, cell classid, cell team)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, "OnPlayerSpawn", &idx))
	{
		amx_Push(&m_amx, team);
		amx_Push(&m_amx, classid);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerDeath(playerid, killerid, reason, bodypart);
int CGameMode::OnPlayerDeath(cell playerid, cell killerid, cell reason, cell bodypart)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, "OnPlayerDeath", &idx))
	{
		amx_Push(&m_amx, bodypart);
		amx_Push(&m_amx, reason);
		amx_Push(&m_amx, killerid);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnVehicleDeath(vehicleid, killerid);
int CGameMode::OnVehicleDeath(cell vehicleid, cell killerid)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, "OnVehicleDeath", &idx))
	{
		amx_Push(&m_amx, killerid);
		amx_Push(&m_amx, vehicleid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerTyping(playerid);
int CGameMode::OnPlayerTyping(cell playerid)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, "OnPlayerTyping", &idx))
	{
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerEndTyping(playerid);
int CGameMode::OnPlayerEndTyping(cell playerid)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&m_amx, "OnPlayerEndTyping", &idx))
	{
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerText(playerid, text[]);
int CGameMode::OnPlayerText(cell playerid, char * szText)
{
	CHECK_INIT();

	int idx;
	cell ret = 1;	// DEFAULT TO 1!
	int orig_strlen = strlen(szText) + 1;

	if (!amx_FindPublic(&m_amx, "OnPlayerText", &idx))
	{
		cell amx_addr, *phys_addr;
		amx_PushString(&m_amx, &amx_addr, &phys_addr, (char*)szText, 0, 0);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
		amx_GetString(szText, phys_addr, 0, orig_strlen);
		amx_Release(&m_amx, amx_addr);
	}

	if (ret) {
		pNetGame->GetPlayerPool()->GetAt((BYTE)playerid)->Say(szText, strlen(szText));
	}

	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerPrivmsg(playerid, toplayerid, text[]);
int CGameMode::OnPlayerPrivmsg(cell playerid, cell toplayerid, char * szText)
{
	CHECK_INIT();

	int idx;
	cell ret = 1;	// DEFAULT TO 1!
	int orig_strlen = strlen((char*)szText) + 1;

	if (!amx_FindPublic(&m_amx, "OnPlayerPrivmsg", &idx))
	{
		cell amx_addr, *phys_addr;
		amx_PushString(&m_amx, &amx_addr, &phys_addr, (char*)szText, 0, 0);
		amx_Push(&m_amx, toplayerid);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
		amx_GetString((char*)szText, phys_addr, 0, orig_strlen);
		amx_Release(&m_amx, amx_addr);
	}

	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerTeamPrivmsg(playerid, text[]);
int CGameMode::OnPlayerTeamPrivmsg(cell playerid, char * szText)
{
	CHECK_INIT();

	int idx;
	cell ret = 1;	// DEFAULT TO 1!
	int orig_strlen = strlen((char*)szText) + 1;

	if (!amx_FindPublic(&m_amx, "OnPlayerTeamPrivmsg", &idx))
	{
		cell amx_addr, *phys_addr;
		amx_PushString(&m_amx, &amx_addr, &phys_addr, (char*)szText, 0, 0);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
		amx_GetString((char*)szText, phys_addr, 0, orig_strlen);
		amx_Release(&m_amx, amx_addr);
	}

	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerCommandText(playerid, cmdtext[]);
int CGameMode::OnPlayerCommandText(cell playerid, char * szCommandText)
{
	CHECK_INIT();

	int idx;
	cell ret = 0;
	int orig_strlen = strlen(szCommandText);

	if (!amx_FindPublic(&m_amx, "OnPlayerCommandText", &idx))
	{
		cell amx_addr, *phys_addr;
		amx_PushString(&m_amx, &amx_addr, &phys_addr, (char*)szCommandText, 0, 0);
		amx_Push(&m_amx, playerid);
		amx_Exec(&m_amx, &ret, idx);
		amx_Release(&m_amx, amx_addr);
	}

	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnRconCommand(cmd[]);
int CGameMode::OnRconCommand(char* szCommand)
{
	CHECK_INIT();

	int idx;
	cell ret = 1;
	int orig_strlen = strlen(szCommand);

	if (!amx_FindPublic(&m_amx, "OnRconCommand", &idx))
	{
		cell amx_addr, *phys_addr;
		amx_PushString(&m_amx, &amx_addr, &phys_addr, szCommand, 0, 0);
		amx_Exec(&m_amx, &ret, idx);
		amx_Release(&m_amx, amx_addr);
	}

	return (int)ret;
}

//----------------------------------------------------------------------------------
