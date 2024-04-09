
//----------------------------------------------------

class CNetGame
{
private:

	CPlayerPool			*m_pPlayerPool;
	CVehiclePool		*m_pVehiclePool;
	int field_8;
	RakClientInterface	*m_pRakClient;
public:
	CNetGame(PCHAR szHostOrIp,int iPort,PCHAR szPlayerName,PCHAR szPass);
};

//----------------------------------------------------
