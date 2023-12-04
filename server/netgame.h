
#ifndef VCMPSRV_NETGAME_H
#define VCMPSRV_NETGAME_H

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

	char _gap0[2280];

	void UpdateNetwork();

public:
	CNetGame();
	~CNetGame();

	void Init();
	void ShutdownForGameModeRestart();

	RakServerInterface * GetRakServer() { return m_pRak; };

	void Process();

	void PlayerSync(Packet *p);
	void AimSync(Packet *p);
	void VehicleSync(Packet *p);
	void PassengerSync(Packet *p);

	void MasterServerAnnounce();
	void LoadBanList();
	DWORD GetCount();
	void ProcessGameTime();

	// CLASS SYSTEM
	int					m_iSpawnsAvailable;

	BYTE field_8A1;

	DWORD field_8A3;
	BYTE field_8A7;
};

#endif
