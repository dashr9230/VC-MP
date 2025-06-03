
#include <time.h>

#include "netgame.h"
#include "../raknet/RakNetworkFactory.h"

extern CConfig *pServerConfig;

int n_Pickups;

//----------------------------------------------------

CNetGame::CNetGame(int iMaxPlayers, int iPort, int iGameType, 
				   char * szPassword, char * szGameFile,
				   BYTE byteFriendlyFire, BYTE byteShowOnRadar)
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

	// Setup pickup pool
	m_pPickUpPool = new CPickUpPool();
	n_Pickups = m_pPickUpPool->InitialiseFromConfig(pServerConfig);

	// Setup the init positions.
	SetupInitPositions();

	// Init the game logic.
	m_pGameLogic = new CGameModeGeneric();

	// Flag we're in a running state.
	m_iGameState = GAMESTATE_RUNNING;

	// Set the ff option
	m_byteFriendlyFire = byteFriendlyFire;

	// Set the show player on radar option
	m_byteShowOnRadar = byteShowOnRadar;

	MasterServerAnnounce();

	srand(time(NULL));

	// TODO: CNetGame::CNetGame
}

//----------------------------------------------------

CNetGame::~CNetGame()
{
	logprintf("--- Server Shutting Down.");
	UnRegisterRPCs(m_pRak);
	RakNetworkFactory::DestroyRakServerInterface(m_pRak);
	delete m_pPlayerPool;
}

//----------------------------------------------------

void CNetGame::Process()
{
	UpdateNetwork();

	// TODO: CNetGame::Process
}

//----------------------------------------------------

void CNetGame::UpdateNetwork()
{
	Packet* p;
	unsigned char packetIdentifier;

	while(p=m_pRak->Receive())
	{
		packetIdentifier = GetPacketID(p);

		switch(packetIdentifier) {

		case ID_DISCONNECTION_NOTIFICATION:
			m_pPlayerPool->Delete((BYTE)p->playerIndex,1);
			break;
		case ID_CONNECTION_LOST:
			m_pPlayerPool->Delete((BYTE)p->playerIndex,0);
			break;
		case ID_PLAYER_SYNC:
			PlayerSync(p);
			break;
		case ID_AIM_SYNC:
			AimSync(p);
			break;
		case ID_VEHICLE_SYNC:
			VehicleSync(p);
			break;
		case ID_PASSENGER_SYNC:
			PassengerSync(p);
			break;
		}

		m_pRak->DeallocatePacket(p);
	}
}

//----------------------------------------------------

void CNetGame::BroadcastData( RakNet::BitStream *bitStream,
							  PacketPriority priority,
							  PacketReliability reliability,
							  char orderingStream,
							  BYTE byteExcludedPlayer )
{
	BYTE x=0;
	float fDistance;
	BOOL bShouldSend;
	int r=0;
	BYTE byteSpectateID=INVALID_PLAYER_ID;

	while(x!=MAX_PLAYERS) {
		if( (m_pPlayerPool->GetSlotState(x) == TRUE) && 
			(x != byteExcludedPlayer) ) {

			bShouldSend = FALSE;
			byteSpectateID = m_pPlayerPool->GetAt(x)->GetSpectate();
			if(byteSpectateID == INVALID_PLAYER_ID || m_pPlayerPool->GetSlotState(byteSpectateID) != TRUE) {
				fDistance = m_pPlayerPool->GetDistanceFromPlayerToPlayer(byteExcludedPlayer,x);
			} else {
				fDistance = m_pPlayerPool->GetDistanceFromPlayerToPlayer(byteExcludedPlayer,byteSpectateID);
			}

			if(fDistance < 250.0f) {
				bShouldSend = TRUE;
			} else {
				// If not within said distance, broadcast
				// randomly once in ten.
				r = (int)(rand() % 10);
				if(!r) bShouldSend = TRUE;
			}

			if(bShouldSend) {
				m_pRak->Send(bitStream,priority,reliability,
					orderingStream,m_pRak->GetPlayerIDFromIndex(x),FALSE);
			}
		}
		x++;
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

void CNetGame::PassengerSync(Packet *p)
{
	CPlayer * pPlayer = GetPlayerPool()->GetAt((BYTE)p->playerIndex);
	RakNet::BitStream bsPassengerSync((PCHAR)p->data, p->length, FALSE);
	RakNet::BitStream bsPassengerSend;

	BYTE		bytePacketID=0;
	BYTE		byteVehicleID=0;
	UINT		uiPassengerSeat;
	float		x,y,z;

	bsPassengerSync.Read(bytePacketID);
	bsPassengerSync.Read(byteVehicleID);
	bsPassengerSync.Read(uiPassengerSeat);
	bsPassengerSync.Read(x);
	bsPassengerSync.Read(y);
	bsPassengerSync.Read(z);

	// TODO: CNetGame::PassengerSync
}

//----------------------------------------------------

void CNetGame::SetupInitPositions()
{
	char *szParseMe;

	// Init Player Pos
	szParseMe = pServerConfig->GetConfigEntryAsString("PLAYERPOS");
	if(!szParseMe) {
		logprintf("I can't init a network game because it's missing a PLAYERPOS setting.");
		exit(1);
	}
	sscanf(szParseMe,"%f%f%f",&m_vecInitPlayerPos.X,&m_vecInitPlayerPos.Y,&m_vecInitPlayerPos.Z);

	// Init Camera Pos
	szParseMe = pServerConfig->GetConfigEntryAsString("CAMPOS");
	if(!szParseMe) {
		logprintf("I can't init a network game because it's missing a CAMPOS setting.");
		exit(1);
	}
	sscanf(szParseMe,"%f%f%f",&m_vecInitCameraPos.X,&m_vecInitCameraPos.Y,&m_vecInitCameraPos.Z);

	// Init Camera Look
	szParseMe = pServerConfig->GetConfigEntryAsString("CAMLOOK");
	if(!szParseMe) {
		logprintf("I can't init a network game because it's missing a CAMLOOK setting.");
		exit(1);
	}
	sscanf(szParseMe,"%f%f%f",&m_vecInitCameraLook.X,&m_vecInitCameraLook.Y,&m_vecInitCameraLook.Z);

	// Init World Bounds
	szParseMe = pServerConfig->GetConfigEntryAsString("WORLDBOUNDS");
	if(!szParseMe) {
		logprintf("I can't init a network game because it's missing a WORLDBOUNDS setting.");
		exit(1);
	}
	sscanf(szParseMe,"%f%f%f%f",&m_WorldBounds[0],&m_WorldBounds[1],&m_WorldBounds[2],&m_WorldBounds[3]);
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

void CNetGame::MasterServerAnnounce()
{
	char szPort[256];
	sprintf(szPort, "%i", iListenPort);

#ifdef WIN32
	ShellExecute(0, "open", "announce.exe", szPort, NULL, SW_HIDE);
#else
	char szAnnounceCmd[256];
	sprintf(szAnnounceCmd, "./announce %s &", szPort);
	system(szAnnounceCmd);
#endif
}

//----------------------------------------------------
