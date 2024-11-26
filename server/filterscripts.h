
#ifndef VCMPSRV_FILTERSCRIPTS_H
#define VCMPSRV_FILTERSCRIPTS_H

class CFilterScripts
{
private:
	AMX* m_pFilterScripts[MAX_FILTER_SCRIPTS];
	int m_iFilterScriptCount;
	CScriptTimers* m_pScriptTimers;
public:
	CFilterScripts();
	~CFilterScripts();

	bool LoadFilterScript(char* pFileName);
	void UnloadFilterScripts();
	void Frame(float fElapsedTime);

	int CallPublic(char* szFuncName);

	int OnPlayerConnect(cell playerid);
	int OnPlayerVersion(cell playerid, cell version);
	int OnPlayerDisconnect(cell playerid, cell reason);
	int OnPlayerSpawn(cell playerid, cell classid, cell team);
	int OnPlayerDeath(cell playerid, cell killerid, cell reason, cell bodypart);
	int OnVehicleSpawn(cell vehicleid);
	int OnVehicleDeath(cell vehicleid, cell killerid);
	int OnPlayerTyping(cell playerid);
	int OnPlayerEndTyping(cell playerid);
	int OnPlayerText(cell playerid, char* szText);
	int OnPlayerPrivmsg(cell playerid, cell toplayerid, char* szText);
	int OnPlayerTeamPrivmsg(cell playerid, char* szText);
	int OnPlayerCommandText(cell playerid, char* szCommandText);
	int OnPlayerInfoChange(cell playerid);
	int OnPlayerRequestClass(cell playerid, cell classid, cell skinid);
	int OnPlayerRequestSpawn(cell playerid);
	int OnPlayerEnterVehicle(cell playerid, cell vehicleid, cell ispassenger);
	int OnPlayerExitVehicle(cell playerid, cell vehicleid);
	int OnPlayerStateChange(cell playerid, cell newstate, cell oldstate);
	int OnPlayerEnterCheckpoint(cell playerid);
	int OnPlayerLeaveCheckpoint(cell playerid);
	int OnRconCommand(char* szCommand);
};

#endif
