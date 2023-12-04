
#include "main.h"

int AMXAPI aux_LoadProgram(AMX* amx, char* filename);
void AMXPrintError(CGameMode* pGameMode, AMX *amx, int error);

char szGameModeFileName[256];

//----------------------------------------------------------------------------------

CGameMode::CGameMode()
{
	m_bInitialised = false;
	m_bSleeping = false;
	m_pScriptTimers = new CScriptTimers;
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


	// TODO: CGameMode::Load

	return false;
}

//----------------------------------------------------------------------------------

void CGameMode::Unload()
{
	// TODO: CGameMode::Unload
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
