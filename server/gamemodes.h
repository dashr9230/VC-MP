
#ifndef VCMPSRV_GAMEMODES_H
#define VCMPSRV_GAMEMODES_H

class CGameMode
{
private:
	bool m_bInitialised;
	bool field_69;

	CScriptTimers* m_pScriptTimers;
public:
	CGameMode();

	bool Load(char* pFileName);
	void Unload();

};

#endif
