
#ifndef VCMPSRV_NETGAME_H
#define VCMPSRV_NETGAME_H

#define MAX_SPAWNS 50

#define GAMESTATE_RUNNING	 1

class CNetGame
{
private:

	CPlayerPool					*m_pPlayerPool;
	CVehiclePool				*m_pVehiclePool;
	CPickUpPool					*m_pPickUpPool;

	RakServerInterface			*m_pRak;

	int	 m_iGameState;

	CGameMode					*m_pGameMode;
	CFilterScripts				*m_pFilterScripts;

	int							m_iCurrentGameModeIndex;
	int							m_iCurrentGameModeRepeat;
	BOOL						m_bFirstGameModeLoaded;

	void UpdateNetwork();

public:
	CNetGame();
	~CNetGame();

	void Init();
	void ShutdownForGameModeRestart();
	BOOL SetNextScriptFile(char *szFile);

	CVehiclePool * GetVehiclePool() { return m_pVehiclePool; };
	CPickUpPool * GetPickupPool() { return m_pPickUpPool; };
	RakServerInterface * GetRakServer() { return m_pRak; };
	CGameMode * GetGameMode() { return m_pGameMode; };

	void Process();

	void PlayerSync(Packet *p);
	void AimSync(Packet *p);
	void VehicleSync(Packet *p);
	void PassengerSync(Packet *p);

	void MasterServerAnnounce();
	void LoadBanList();
	DWORD GetCount();
	void ProcessGameTime();
	int CanFileBeOpenedForReading(char * filename);

	// CLASS SYSTEM
	int					m_iSpawnsAvailable;
	PLAYER_SPAWN_INFO	m_AvailableSpawns[MAX_SPAWNS];
	void AddSpawn(PLAYER_SPAWN_INFO *pSpawnInfo);

	BYTE field_8A1;

	DWORD field_8A3;
	BYTE field_8A7;
};

#endif
