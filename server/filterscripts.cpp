
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

int CFilterScripts::OnPlayerPrivmsg(cell playerid, cell toplayerid, unsigned char* szText)
{
	int idx;
	cell ret = 1;	// DEFAULT TO 1!

	int orig_strlen = strlen((char*)szText) + 1;

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnPlayerPrivmsg", &idx))
			{
				cell amx_addr, *phys_addr;
				amx_PushString(m_pFilterScripts[i], &amx_addr, &phys_addr, (char*)szText, 0, 0);
				amx_Push(m_pFilterScripts[i], toplayerid);
				amx_Push(m_pFilterScripts[i], playerid);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
				amx_GetString((char*)szText, phys_addr, 0, orig_strlen);
				amx_Release(m_pFilterScripts[i], amx_addr);
				if (!ret) return 0; // Callback returned 0, so exit and don't display the text.
			}
		}
	}
	return (int)ret;
}

int CFilterScripts::OnPlayerTeamPrivmsg(cell playerid, unsigned char* szText)
{
		int idx;
	cell ret = 1;	// DEFAULT TO 1!

	int orig_strlen = strlen((char*)szText) + 1;

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnPlayerTeamPrivmsg", &idx))
			{
				cell amx_addr, *phys_addr;
				amx_PushString(m_pFilterScripts[i], &amx_addr, &phys_addr, (char*)szText, 0, 0);
				amx_Push(m_pFilterScripts[i], playerid);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
				amx_GetString((char*)szText, phys_addr, 0, orig_strlen);
				amx_Release(m_pFilterScripts[i], amx_addr);
				if (!ret) return 0; // Callback returned 0, so exit and don't display the text.
			}
		}
	}
	return (int)ret;
}

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
				if (!ret) return ret;
			}
		}
	}
	return (int)ret;
}

int CFilterScripts::OnPlayerSpawn(cell playerid, cell classid, cell teamid)
{
	int idx;
	cell ret = 0;

	for (int i=0; i<MAX_FILTER_SCRIPTS; i++)
	{
		if (m_pFilterScripts[i])
		{
			if (!amx_FindPublic(m_pFilterScripts[i], "OnPlayerSpawn", &idx))
			{
				amx_Push(m_pFilterScripts[i], teamid);
				amx_Push(m_pFilterScripts[i], classid);
				amx_Push(m_pFilterScripts[i], playerid);
				amx_Exec(m_pFilterScripts[i], &ret, idx);
				if (!ret) return ret;
			}
		}
	}
	return (int)ret;
}

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