
#ifndef VCMPSRV_NETGAME_H
#define VCMPSRV_NETGAME_H

#define MAX_SPAWNS 50

#define GAMESTATE_RUNNING	 1

typedef struct _GAME_SETTINGS {

	char _pad0[21];

} GAME_SETTINGS;

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

	CPlayerPool * GetPlayerPool() { return m_pPlayerPool; };
	CVehiclePool * GetVehiclePool() { return m_pVehiclePool; };
	CPickUpPool * GetPickupPool() { return m_pPickUpPool; };
	RakServerInterface * GetRakServer() { return m_pRak; };
	CGameMode * GetGameMode() { return m_pGameMode; };
	CFilterScripts * GetFilterScripts() { return m_pFilterScripts; };

	void Process();

	void BroadcastData( RakNet::BitStream *bitStream, PacketPriority priority,
						PacketReliability reliability,
						char orderingStream,
						BYTE byteExcludedPlayer );

	void PlayerSync(Packet *p);
	void AimSync(Packet *p);
	void VehicleSync(Packet *p);
	void PassengerSync(Packet *p);

	void MasterServerAnnounce();
	void KickPlayer(BYTE byteKickPlayer);
	void AddBan(char * ip_mask);
	void LoadBanList();
	DWORD GetCount();
	void ProcessGameTime();
	void SendGameSettingsToAll();
	void SetWepDam(BYTE byteWeaponID, BYTE byteDamage);

	int CanFileBeOpenedForReading(char * filename) {
		FILE *f;
		if(f=fopen(filename,"r")) {
			fclose(f);
			return 1;
		}
		return 0;
	}

	void SetSleep(int iSleepTime)
	{
		SLEEP(iSleepTime);
	}

	void SetupWepDam()
	{
		for(BYTE i = 1; i != 33; i++)
		{
			m_byteWeaponDamage[i] = 0;
		}
	}

	// CLASS SYSTEM
	int					m_iSpawnsAvailable;
	PLAYER_SPAWN_INFO	m_AvailableSpawns[MAX_SPAWNS];
	void AddSpawn(PLAYER_SPAWN_INFO *pSpawnInfo);

	VECTOR		m_vecInitPlayerPos;
	VECTOR		m_vecInitCameraPos;
	VECTOR		m_vecInitCameraLook;
	float		m_WorldBounds[4]; // pos_x neg_x pos_y neg_y

	char _gap89C[5];

	BYTE		m_byteShowOnRadar;

	char _gap8A2;

	DWORD		field_8A3;
	BYTE		m_byteWorldTime;

	char _gap8A8[5];

	GAME_SETTINGS m_GameSettings;
	BYTE m_byteWeaponDamage[33];
};

#endif
