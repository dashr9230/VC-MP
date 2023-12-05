
#ifndef VCMPSRV_GAMEMODES_H
#define VCMPSRV_GAMEMODES_H

extern char szGameModeFileName[256];

class CGameMode
{
private:
	AMX m_amx;
	bool m_bInitialised;
	bool m_bSleeping;
	float m_fSleepTime;

	CScriptTimers* m_pScriptTimers;
public:
	CGameMode();

	char* GetFileName() { return &szGameModeFileName[0]; };
	CScriptTimers* GetTimers() { return m_pScriptTimers; };

	bool Load(char* pFileName);
	void Unload();
	void Frame(float fElapsedTime);

};

#endif
