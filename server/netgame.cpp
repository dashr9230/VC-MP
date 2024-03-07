
#include "netgame.h"
#include "../raknet/RakNetworkFactory.h"

extern CConfig *pServerConfig;

//----------------------------------------------------

CNetGame::CNetGame(int iMaxPlayers, int iPort, int iGameType,
				   char * szPassword)
{
	// Setup raknet
	m_pRak = RakNetworkFactory::GetRakServerInterface();

	m_pRak->InitializeSecurity(0,0);
	m_pRak->Start(iMaxPlayers,0,5,iPort);
	m_pRak->StartOccasionalPing();
	m_pRak->StartSynchronizedRandomInteger();

	LoadBanList();

	if(szPassword != NULL) {
		m_pRak->SetPassword(szPassword);
	}

	// Register our RPC handlers
	RegisterRPCs(m_pRak);

	// Setup player pool
	m_pPlayerPool = new CPlayerPool();

	// Setup vehicle pool
	m_pVehiclePool = new CVehiclePool();
	m_pVehiclePool->InitialiseFromConfig(pServerConfig);


}

//----------------------------------------------------

void CNetGame::LoadBanList()
{
	FILE * fileBanList = fopen("vcmp-svr.banlist","r");
	if(!fileBanList) return;

	char ban_ip[256];

	while(!feof(fileBanList)) {
		fgets(ban_ip,256,fileBanList);
		ban_ip[strlen(ban_ip) - 1] = '\0';
		m_pRak->AddToBanList(ban_ip);
	}

	fclose(fileBanList);
}

//----------------------------------------------------
