
#include "../main.h"

extern CChatWindow   *pChatWindow;

//----------------------------------------------------

CNetGame::CNetGame(PCHAR szHostOrIp, int iPort, 
				   PCHAR szPlayerName, PCHAR szPass)
{
	// Setup player pool
	m_pPlayerPool = new CPlayerPool();
	m_pPlayerPool->SetLocalPlayerName(szPlayerName);

	m_pVehiclePool = new CVehiclePool();

	m_pRakClient = RakNetworkFactory::GetRakClientInterface();

	//m_pRakClient->InitializeSecurity(0,0);

	RegisterRPCs(m_pRakClient);

	m_pRakClient->SetPassword(szPass);
	m_pRakClient->Connect(szHostOrIp,iPort,(iPort+1),0,5);
	m_pRakClient->StartOccasionalPing();

	field_10 = 1;
	if(pChatWindow) pChatWindow->AddDebugMessage("Connecting to %s:%d..",szHostOrIp,iPort);

	m_pGameLogic = NULL;
	field_54 = 0;
	field_14 = GetTickCount();
	field_18 = GetTickCount();
	field_1C = 0;
}

//----------------------------------------------------

CNetGame::~CNetGame()
{
	m_pRakClient->Disconnect(0);
	UnRegisterRPCs(m_pRakClient);
	RakNetworkFactory::DestroyRakClientInterface(m_pRakClient);
	delete m_pPlayerPool;
	delete m_pGameLogic;
}

//----------------------------------------------------

void CNetGame::InitGameLogic()
{
	m_pGameLogic = new CGameModeGeneric();
}

//----------------------------------------------------

void CNetGame::UpdateNetwork()
{
	Packet* pkt=NULL;

	while((pkt = m_pRakClient->Receive()))
	{
		switch(pkt->data[0])
		{
		case ID_CONNECTION_BANNED:
			pChatWindow->AddDebugMessage("You're banned from the server.");
			break;
		case ID_NO_FREE_INCOMING_CONNECTIONS:
			pChatWindow->AddDebugMessage("The server is full.");
			break;
		case ID_DISCONNECTION_NOTIFICATION:
			pChatWindow->AddDebugMessage("Disconnected.");
			break;
		case ID_CONNECTION_LOST:
			pChatWindow->AddDebugMessage("Lost connection to the server.");
			break;
		case ID_INVALID_PASSWORD:
			pChatWindow->AddDebugMessage("Wrong server password.");
			break;
		case ID_MODIFIED_PACKET:
			m_pRakClient->Disconnect(100);
			break;
		case ID_CONNECTION_REQUEST_ACCEPTED:
			ConnectionSucceeded(pkt);
			break;
		case ID_PLAYER_SYNC:
			PlayerSync(pkt);
			break;
		case ID_AIM_SYNC:
			AimSync(pkt);
			break;
		case ID_VEHICLE_SYNC:
			VehicleSync(pkt);
			break;
		}

		m_pRakClient->DeallocatePacket(pkt);
	}
}

//----------------------------------------------------

void CNetGame::PlayerSync(Packet *p)
{
	// TODO: CNetGame::PlayerSync
}

//----------------------------------------------------

void CNetGame::AimSync(Packet *p)
{
	// TODO: CNetGame::AimSync
}

//----------------------------------------------------

void CNetGame::VehicleSync(Packet *p)
{
	// TODO: CNetGame::VehicleSync
}

//----------------------------------------------------

void CNetGame::ConnectionSucceeded(Packet *p)
{
	// TODO: CNetGame::ConnectionSucceeded
}
