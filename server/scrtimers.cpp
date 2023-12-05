
#include "main.h"

CScriptTimers::CScriptTimers()
{
	m_dwTimerCount = 0;
}

//----------------------------------------------------------------------------------

DWORD CScriptTimers::New(char* szScriptFunc, int iInterval, BOOL bRepeating, AMX* pAMX)
{
	m_dwTimerCount++;

	ScriptTimer_s* NewTimer = new ScriptTimer_s;

	//if(iInterval < 500) iInterval = 500;

	strncpy(NewTimer->szScriptFunc, szScriptFunc, 255);
	NewTimer->iTotalTime = iInterval;
	NewTimer->iRemainingTime = iInterval;
	NewTimer->bRepeating = bRepeating;
	NewTimer->pAMX = pAMX;
	// Checks if it's called from a filterscript, if not, mark it for destruction at gamemode end
	/*if (pAMX == pNetGame->GetGameMode()->GetGameModePointer())
	{
		NewTimer->bFilterscript = false;
		//print("GM");
	}
	else
	{
		NewTimer->bFilterscript = true;
		//print("FS");
	}*/
	m_Timers.insert(DwordTimerMap::value_type(m_dwTimerCount, NewTimer));
	return m_dwTimerCount;
}

//----------------------------------------------------------------------------------

void CScriptTimers::Delete(DWORD dwTimerId)
{
	DwordTimerMap::iterator itor;
	itor = m_Timers.find(dwTimerId);
	if (itor != m_Timers.end())
	{
		SAFE_DELETE(itor->second);
		m_Timers.erase(itor);
	}
}

//----------------------------------------------------------------------------------

void CScriptTimers::Process(int iElapsedTime)
{
	DwordTimerMap::iterator itor;
	CGameMode *pGameMode;
	for (itor = m_Timers.begin(); itor != m_Timers.end(); itor++)
	{
		itor->second->iRemainingTime -= iElapsedTime;
		if (itor->second->iRemainingTime <= 0)
		{
			if (itor->second->bRepeating)
			{
				itor->second->iRemainingTime = itor->second->iTotalTime;

				DwordTimerMap::iterator itor_tmp = ++itor; itor--;

				pGameMode = pNetGame->GetGameMode();
				if (pGameMode)
				{
					int idx;
					if(!amx_FindPublic(itor->second->pAMX, itor->second->szScriptFunc, &idx))
					{
						cell ret;
						amx_Exec(itor->second->pAMX, &ret, idx);
					}
				}
			}
			else
			{
				DwordTimerMap::iterator itor_tmp = ++itor; itor--;

				pGameMode = pNetGame->GetGameMode();
				if (pGameMode)
				{
					int idx;
					if(!amx_FindPublic(itor->second->pAMX, itor->second->szScriptFunc, &idx))
					{
						cell ret;
						amx_Exec(itor->second->pAMX, &ret, idx);
					}
				}
				Delete(itor->first);
			}
		}
		if (itor == m_Timers.end()) break;
	}
}
