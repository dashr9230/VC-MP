
#include "main.h"

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
int amx_CustomInit(AMX *amx);

//----------------------------------------------------------------------------------

CFilterScripts::CFilterScripts()
{
	m_pScriptTimers = new CScriptTimers;

	m_iFilterScriptCount = 0;
	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
		m_pFilterScripts[i] = NULL;
}

//----------------------------------------------------------------------------------

CFilterScripts::~CFilterScripts()
{
	UnloadFilterScripts();
	SAFE_DELETE(m_pScriptTimers);
}

//----------------------------------------------------------------------------------

bool CFilterScripts::LoadFilterScript(char* pFileName)
{
	if (m_iFilterScriptCount >= MAX_FILTER_SCRIPTS)
		return false;

	FILE* f = fopen(pFileName, "rb");
	if (!f) return false;
	fclose(f);

	m_pFilterScripts[m_iFilterScriptCount] = new AMX;
	AMX* amx = m_pFilterScripts[m_iFilterScriptCount];

	memset((void*)amx, 0, sizeof(AMX));
	int err = aux_LoadProgram(amx, pFileName);
	if (err != AMX_ERR_NONE)
	{
		logprintf("Failed to load '%s' filter script.", pFileName);
		return false;
	}

	amx_CoreInit(amx);
	amx_FloatInit(amx);
	amx_StringInit(amx);
	amx_FileInit(amx);
	amx_TimeInit(amx);
	amx_CustomInit(amx);

	int tmp;
	if (!amx_FindPublic(amx, "OnFilterScriptInit", &tmp))
		amx_Exec(amx, (cell*)&tmp, tmp);

	m_iFilterScriptCount++;

	return true;
}

//----------------------------------------------------------------------------------

void CFilterScripts::UnloadFilterScripts()
{
	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			int tmp;
			if (!amx_FindPublic(m_pFilterScripts[i], "OnFilterScriptExit", &tmp))
				amx_Exec(m_pFilterScripts[i], (cell*)&tmp, tmp);

			// Do the other stuff from before
			aux_FreeProgram(m_pFilterScripts[i]);
			amx_TimeCleanup(m_pFilterScripts[i]);
			amx_FileCleanup(m_pFilterScripts[i]);
			amx_StringCleanup(m_pFilterScripts[i]);
			amx_FloatCleanup(m_pFilterScripts[i]);
			amx_CoreCleanup(m_pFilterScripts[i]);
			SAFE_DELETE(m_pFilterScripts[i]);
		}
	}

	m_iFilterScriptCount = 0;
}

//----------------------------------------------------------------------------------

void CFilterScripts::Frame(float fElapsedTime)
{
	if (m_pScriptTimers)
		m_pScriptTimers->Process((DWORD)(fElapsedTime * 1000.0f));
}

//----------------------------------------------------------------------------------

int CFilterScripts::CallPublic(char* szFuncName)
{
	int idx;
	cell ret = 0;

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], szFuncName, &idx))
			{
				amx_Exec(m_pFilterScripts[i], &ret, idx);
				if (!ret) return ret;
			}
		}
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerConnect(playerid);
int CFilterScripts::OnPlayerConnect(cell playerid)
{
	int idx;
	cell ret = 0;

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnPlayerConnect", &idx))
			{
				amx_Push(m_pFilterScripts[i], playerid);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
				if (!ret) return ret;
			}
		}
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerVersion(playerid, version);
int CFilterScripts::OnPlayerVersion(cell playerid, cell version)
{
	int idx;
	cell ret = 0;

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnPlayerVersion", &idx))
			{
				amx_Push(m_pFilterScripts[i], version);
				amx_Push(m_pFilterScripts[i], playerid);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
				if (!ret) return ret;
			}
		}
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerDisconnect(playerid, reason);
int CFilterScripts::OnPlayerDisconnect(cell playerid, cell reason)
{
	int idx;
	cell ret = 0;

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnPlayerDisconnect", &idx))
			{
				amx_Push(m_pFilterScripts[i], reason);
				amx_Push(m_pFilterScripts[i], playerid);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
				if (!ret) return 0;
			}
		}
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerSpawn(playerid);
int CFilterScripts::OnPlayerSpawn(cell playerid, cell classid, cell team)
{
	int idx;
	cell ret = 0;

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnPlayerSpawn", &idx))
			{
				amx_Push(m_pFilterScripts[i], team);
				amx_Push(m_pFilterScripts[i], classid);
				amx_Push(m_pFilterScripts[i], playerid);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
				if (!ret) return ret;
			}
		}
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerDeath(playerid, killerid, reason, bodypart);
int CFilterScripts::OnPlayerDeath(cell playerid, cell killerid, cell reason, cell bodypart)
{
	int idx;
	cell ret = 0;

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnPlayerDeath", &idx))
			{
				amx_Push(m_pFilterScripts[i], bodypart);
				amx_Push(m_pFilterScripts[i], reason);
				amx_Push(m_pFilterScripts[i], killerid);
				amx_Push(m_pFilterScripts[i], playerid);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
				if (!ret) return ret;
			}
		}
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnVehicleSpawn(vehicleid);
int CFilterScripts::OnVehicleSpawn(cell vehicleid)
{
	int idx;
	cell ret = 0;

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnVehicleSpawn", &idx))
			{
				amx_Push(m_pFilterScripts[i], vehicleid);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
				if (!ret) return ret;
			}
		}
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnVehicleDeath(vehicleid, killerid);
int CFilterScripts::OnVehicleDeath(cell vehicleid, cell killerid)
{
	int idx;
	cell ret = 0;

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnVehicleDeath", &idx))
			{
				amx_Push(m_pFilterScripts[i], killerid);
				amx_Push(m_pFilterScripts[i], vehicleid);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
			}
		}
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerTyping(playerid);
int CFilterScripts::OnPlayerTyping(cell playerid)
{
	int idx;
	cell ret = 0;

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnPlayerTyping", &idx))
			{
				amx_Push(m_pFilterScripts[i], playerid);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
			}
		}
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerEndTyping(playerid);
int CFilterScripts::OnPlayerEndTyping(cell playerid)
{
	int idx;
	cell ret = 0;

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnPlayerEndTyping", &idx))
			{
				amx_Push(m_pFilterScripts[i], playerid);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
			}
		}
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerText(playerid, text[]);
int CFilterScripts::OnPlayerText(cell playerid, char* szText)
{
	int idx;
	cell ret = 1;	// DEFAULT TO 1!

	int orig_strlen = strlen(szText) + 1;

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnPlayerText", &idx))
			{
				cell amx_addr, *phys_addr;
				amx_PushString(m_pFilterScripts[i], &amx_addr, &phys_addr, (char*)szText, 0, 0);
				amx_Push(m_pFilterScripts[i], playerid);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
				amx_GetString(szText, phys_addr, 0, orig_strlen);
				amx_Release(m_pFilterScripts[i], amx_addr);
				if (!ret) return 0; // Callback returned 0, so exit and don't display the text.
			}
		}
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerPrivmsg(playerid, toplayerid, text[]);
int CFilterScripts::OnPlayerPrivmsg(cell playerid, cell toplayerid, char* szText)
{
	int idx;
	cell ret = 1;	// DEFAULT TO 1!

	int orig_strlen = strlen(szText) + 1;

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnPlayerPrivmsg", &idx))
			{
				cell amx_addr, *phys_addr;
				amx_PushString(m_pFilterScripts[i], &amx_addr, &phys_addr, szText, 0, 0);
				amx_Push(m_pFilterScripts[i], toplayerid);
				amx_Push(m_pFilterScripts[i], playerid);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
				amx_GetString(szText, phys_addr, 0, orig_strlen);
				amx_Release(m_pFilterScripts[i], amx_addr);
				if (!ret) return 0; // Callback returned 0, so exit and don't display the text.
			}
		}
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerTeamPrivmsg(playerid, text[]);
int CFilterScripts::OnPlayerTeamPrivmsg(cell playerid, char* szText)
{
	int idx;
	cell ret = 1;	// DEFAULT TO 1!

	int orig_strlen = strlen(szText) + 1;

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnPlayerTeamPrivmsg", &idx))
			{
				cell amx_addr, *phys_addr;
				amx_PushString(m_pFilterScripts[i], &amx_addr, &phys_addr, szText, 0, 0);
				amx_Push(m_pFilterScripts[i], playerid);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
				amx_GetString(szText, phys_addr, 0, orig_strlen);
				amx_Release(m_pFilterScripts[i], amx_addr);
				if (!ret) return 0; // Callback returned 0, so exit and don't display the text.
			}
		}
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerCommandText(playerid, cmdtext[]);
int CFilterScripts::OnPlayerCommandText(cell playerid, char* szCommandText)
{
	int idx;
	cell ret = 0;

	int orig_strlen = strlen(szCommandText);

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnPlayerCommandText", &idx))
			{
				cell amx_addr, *phys_addr;
				amx_PushString(m_pFilterScripts[i], &amx_addr, &phys_addr, szCommandText, 0, 0);
				amx_Push(m_pFilterScripts[i], playerid);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
				amx_Release(m_pFilterScripts[i], amx_addr);
				if (ret) return 1; // Callback returned 1, so the command was accepted!
			}
		}
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerInfoChange(playerid);
int CFilterScripts::OnPlayerInfoChange(cell playerid)
{
	int idx;
	cell ret = 0;

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnPlayerInfoChange", &idx))
			{
				amx_Push(m_pFilterScripts[i], playerid);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
			}
		}
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerRequestClass(playerid, classid, skinid);
int CFilterScripts::OnPlayerRequestClass(cell playerid, cell classid, cell skinid)
{
	int idx;
	cell ret = 1;	// DEFAULT TO 1!

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnPlayerRequestClass", &idx))
			{
				amx_Push(m_pFilterScripts[i], skinid);
				amx_Push(m_pFilterScripts[i], classid);
				amx_Push(m_pFilterScripts[i], playerid);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
			}
		}
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerRequestSpawn(playerid);
int CFilterScripts::OnPlayerRequestSpawn(cell playerid)
{
	int idx;
	cell ret = 1;	// DEFAULT TO 1!

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnPlayerRequestSpawn", &idx))
			{
				amx_Push(m_pFilterScripts[i], playerid);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
				if (!ret) return ret;
			}
		}
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
int CFilterScripts::OnPlayerEnterVehicle(cell playerid, cell vehicleid, cell ispassenger)
{
	int idx;
	cell ret = 0;

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnPlayerEnterVehicle", &idx))
			{
				amx_Push(m_pFilterScripts[i], ispassenger);
				amx_Push(m_pFilterScripts[i], vehicleid);
				amx_Push(m_pFilterScripts[i], playerid);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
			}
		}
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerExitVehicle(playerid, vehicleid);
int CFilterScripts::OnPlayerExitVehicle(cell playerid, cell vehicleid)
{
	int idx;
	cell ret = 0;

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnPlayerExitVehicle", &idx))
			{
				amx_Push(m_pFilterScripts[i], vehicleid);
				amx_Push(m_pFilterScripts[i], playerid);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
			}
		}
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerStateChange(playerid, newstate, oldstate);
int CFilterScripts::OnPlayerStateChange(cell playerid, cell newstate, cell oldstate)
{
	int idx;
	cell ret = 0;

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnPlayerStateChange", &idx))
			{
				amx_Push(m_pFilterScripts[i], oldstate);
				amx_Push(m_pFilterScripts[i], newstate);
				amx_Push(m_pFilterScripts[i], playerid);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
			}
		}
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerEnterCheckpoint(playerid);
int CFilterScripts::OnPlayerEnterCheckpoint(cell playerid)
{
	int idx;
	cell ret = 0;

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnPlayerEnterCheckpoint", &idx))
			{
				amx_Push(m_pFilterScripts[i], playerid);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
			}
		}
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnPlayerLeaveCheckpoint(playerid);
int CFilterScripts::OnPlayerLeaveCheckpoint(cell playerid)
{
	int idx;
	cell ret = 0;

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnPlayerLeaveCheckpoint", &idx))
			{
				amx_Push(m_pFilterScripts[i], playerid);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
			}
		}
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------

// forward OnRconCommand(cmd[]);
int CFilterScripts::OnRconCommand(char* szCommand)
{
	int idx;
	cell ret = 1;

	int orig_strlen = strlen(szCommand);

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnRconCommand", &idx))
			{
				cell amx_addr, *phys_addr;
				amx_PushString(m_pFilterScripts[i], &amx_addr, &phys_addr, szCommand, 0, 0);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
				amx_Release(m_pFilterScripts[i], amx_addr);
				if (ret) return 1;
			} 
		}
	}
	return (int)ret;
}

//----------------------------------------------------------------------------------
