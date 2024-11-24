
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
	~CGameMode();

	char* GetFileName() { return &szGameModeFileName[0]; };
	CScriptTimers* GetTimers() { return m_pScriptTimers; };

	bool Load(char* pFileName);
	void Unload();
	void Frame(float fElapsedTime);

	int CallPublic(char* szFuncName);

	int OnPlayerConnect(cell playerid);
	int OnPlayerVersion(cell playerid, cell version);
	int OnPlayerDisconnect(cell playerid, cell reason);
	int OnPlayerSpawn(cell playerid, cell classid, cell team);
	int OnPlayerDeath(cell playerid, cell killerid, cell reason, cell bodypart);
	int OnVehicleDeath(cell vehicleid, cell killerid);
	int OnPlayerTyping(cell playerid);
	int OnPlayerEndTyping(cell playerid);
	int OnPlayerText(cell playerid, char * szText);
	int OnPlayerPrivmsg(cell playerid, cell toplayerid, char * szText);
	int OnPlayerTeamPrivmsg(cell playerid, char * szText);
	int OnPlayerCommandText(cell playerid, char * szCommandText);
	int OnRconCommand(char* szCommand);
};

#endif
