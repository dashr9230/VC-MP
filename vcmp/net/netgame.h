
#define GAMESTATE_CONNECTING	1

class CNetGame
{
private:

	CPlayerPool			*m_pPlayerPool;
	CVehiclePool		*m_pVehiclePool;
	RakClientInterface	*m_pRakClient;

	int					m_iGameState;

public:

	CNetGame(PCHAR szHostOrIp,int iPort,PCHAR szPlayerName,PCHAR szPass);

};

//----------------------------------------------------
