
#ifndef VCMPSRV_TIMERS_H
#define VCMPSRV_TIMERS_H

struct ScriptTimer_s
{
	char szScriptFunc[255];
	int iTotalTime;
	int iRemainingTime;
	BOOL bRepeating;
	AMX* pAMX;
};

typedef std::map<DWORD, ScriptTimer_s*> DwordTimerMap;

class CScriptTimers
{
private:
	DwordTimerMap m_Timers;
	DWORD m_dwTimerCount;
public:
	CScriptTimers();

	DWORD New(char* szScriptFunc, int iInterval, BOOL bRepeating, AMX* pAMX);
	void Delete(DWORD dwTimerId);
	void Process(int iElapsedTime);
};

#endif
