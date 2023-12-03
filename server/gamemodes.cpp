
#include "main.h"

CGameMode::CGameMode()
{
	m_bInitialised = false;
	field_69 = false;
	m_pScriptTimers = new CScriptTimers;
}

bool CGameMode::Load(char* pFileName)
{
	if (m_bInitialised)
		Unload();

	FILE* f = fopen(pFileName, "rb");
	if (!f) return false;
	fclose(f);

	// TODO: CGameMode::Load

	return false;
}

void CGameMode::Unload()
{

}
