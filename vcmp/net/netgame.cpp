
#include "../main.h"

//----------------------------------------------------

CNetGame::CNetGame(PCHAR szHostOrIp, int iPort,
				   PCHAR szPlayerName, PCHAR szPass)
{
	// Setup player pool
	m_pPlayerPool = new CPlayerPool();
	m_pPlayerPool->SetLocalPlayerName(szPlayerName);

	m_pVehiclePool = new CVehiclePool();

	m_pRakClient = RakNetworkFactory::GetRakClientInterface();

	m_pRakClient->InitializeSecurity(0,0);
}

//----------------------------------------------------

