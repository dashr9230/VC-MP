
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

	RegisterRPCs(m_pRakClient);

	m_pRakClient->SetPassword(szPass);
	m_pRakClient->Connect(szHostOrIp,iPort,(iPort+1),0,5);
	m_pRakClient->StartOccasionalPing();

	m_iGameState = GAMESTATE_CONNECTING;

	// TODO: CNetGame::CNetGame
}

//----------------------------------------------------

