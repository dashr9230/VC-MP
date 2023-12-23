
#pragma once

class CNetGame
{
private:

	CPlayerPool			*m_pPlayerPool;
	CVehiclePool		*m_pVehiclePool;
	RakClientInterface	*m_pRakClient;
	CGameModeGeneric	*m_pGameLogic;

	int field_10;
	DWORD field_14;
	DWORD field_18;
	int field_1C;

	int field_54;

	void UpdateNetwork();

	void PlayerSync(Packet *p);
	void VehicleSync(Packet *p);
	void AimSync(Packet *p);
	void ConnectionSucceeded(Packet *p);

public:
	CNetGame(PCHAR szHostOrIp,int iPort,PCHAR szPlayerName,PCHAR szPass);
	~CNetGame();

	CPlayerPool * GetPlayerPool() { return m_pPlayerPool; };

	void InitGameLogic();
};

//----------------------------------------------------
