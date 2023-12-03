
#ifndef VCMPSRV_TIMERS_H
#define VCMPSRV_TIMERS_H

struct ScriptTimer_s
{

};

typedef std::map<DWORD, ScriptTimer_s*> DwordTimerMap;

class CScriptTimers
{
private:
	DwordTimerMap m_Timers;
	DWORD m_dwTimerCount;
public:
	CScriptTimers();
};

#endif
