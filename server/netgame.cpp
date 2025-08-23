
#include "main.h"

extern int iListenPort;

char szGameModeFile[256];

DWORD count = _cst(21600,600);
DWORD sTime;

//----------------------------------------------------

CNetGame::CNetGame()
{
	// Init member variables
	m_pPlayerPool = NULL;
	m_pVehiclePool = NULL;

	m_pPickUpPool = NULL;

	if(pConsole->GetIntVariable("maxplayers") > MAX_PLAYERS) {
		pConsole->SetIntVariable("maxplayers",MAX_PLAYERS);
	}

	// Setup RakNet
	m_pRak = RakNetworkFactory::GetRakServerInterface();

	LoadBanList();

	// Register our RPC handlers
	RegisterRPCs(m_pRak);

	// TODO: CNetGame::CNetGame()

	SetupWepDam();
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
// Handles rotation and setting of the current
// script file to be used. If szFile is NULL, it
// will attempt to rotate scripts as per configuration.
// returns FALSE if it was not able to set the script,
// true otherwise.

BOOL CNetGame::SetNextScriptFile(char *szFile)
{
	char szCurGameModeConsoleVar[64];
	char szConfigFileName[64];
	char *szTemp;
	int  iConfigRepeatCount=0;

	if(NULL == szFile) {
		// rotate by config

		if(!m_iCurrentGameModeRepeat && m_bFirstGameModeLoaded) {
			// repeats of this script, cycle to the current
			m_iCurrentGameModeIndex++;
		}

		sprintf(szCurGameModeConsoleVar,"gamemode%u",m_iCurrentGameModeIndex);
		szTemp = pConsole->GetStringVariable(szCurGameModeConsoleVar);

		// if the var isn't there then cycle back to 0
		if(!szTemp || !strlen(szTemp)) {
			m_iCurrentGameModeIndex = 0;
			sprintf(szCurGameModeConsoleVar,"gamemode%u",m_iCurrentGameModeIndex);
			szTemp = pConsole->GetStringVariable(szCurGameModeConsoleVar);
		}

		// if it's still NULL then we've got an error.
		if(!szTemp || !strlen(szTemp)) return FALSE;

		sscanf(szTemp,"%s%d",szConfigFileName,&iConfigRepeatCount);

		// set it and verify the file is readable
		sprintf(szGameModeFile,"gamemodes/%s.amx",szConfigFileName);

		if(!CanFileBeOpenedForReading(szGameModeFile)) {
			return FALSE;
		}

		if(!m_iCurrentGameModeRepeat) {
			m_iCurrentGameModeRepeat = iConfigRepeatCount;
		}

		m_iCurrentGameModeRepeat--;

		m_bFirstGameModeLoaded = TRUE;

		return TRUE;

	} else {
		// set the script from szFile

		// set it and verify the file is readable
		sprintf(szGameModeFile,"gamemodes/%s.amx",szFile);

		if(!CanFileBeOpenedForReading(szGameModeFile)) {
			return FALSE;
		}

		m_iCurrentGameModeRepeat = 0;

		return TRUE;
	}
}

//----------------------------------------------------

void CNetGame::Init()
{
	m_iSpawnsAvailable = 0;

	// Setup player pool
	if(!m_pPlayerPool) {
		m_pPlayerPool = new CPlayerPool();
	} else {
		m_pPlayerPool->ResetPlayerScoresAndMoney();
	}

	// Setup vehicle pool
	if(!m_pVehiclePool) {
		m_pVehiclePool = new CVehiclePool();
	}

	// Setup pick up pool
	if(!m_pPickUpPool) {
		m_pPickUpPool = new CPickUpPool();
	}

	// Setup gamemode
	if(!m_pGameMode) {
		m_pGameMode = new CGameMode();
	}

	// Default tags/markers
	m_byteShowOnRadar = 1;

	// Set the default world time for clients.
	m_byteWorldTime = 12;

	// Start the gamemode script.
	m_pGameMode->Load(szGameModeFile);

	// Flag we're in a running state.
	m_iGameState = GAMESTATE_RUNNING;
}

//----------------------------------------------------

void CNetGame::ShutdownForGameModeRestart()
{

}

//----------------------------------------------------





//----------------------------------------------------

#ifdef WIN32

#pragma comment(lib, "winmm.lib")
float GetElapsedTime()
{
	static BOOL bTimerInit = false;
	static BOOL bUsingOPF  = false;
	static LONGLONG nTicksPerSec = 0;

	if (!bTimerInit)
	{
		bTimerInit = true;
		LARGE_INTEGER qwTicksPerSec;
		bUsingOPF = QueryPerformanceFrequency(&qwTicksPerSec);
		if (bUsingOPF) nTicksPerSec = qwTicksPerSec.QuadPart;
	}

	if (bUsingOPF)
	{
		LARGE_INTEGER qwTime;
		QueryPerformanceCounter(&qwTime);
		static LONGLONG llLastTime = qwTime.QuadPart;
		double fElapsedTime = (double)(qwTime.QuadPart - llLastTime) / (double) nTicksPerSec;
		llLastTime = qwTime.QuadPart;
		return (float)fElapsedTime;
	} else {
		double fTime = timeGetTime() * 0.001;
		static double fLastTime = fTime;
		double fElapsedTime = (double)(fTime - fLastTime);
		fLastTime = fTime;
		return (float)fElapsedTime;
	}
}

#else

float GetElapsedTime()
{
	static timeval lasttv;
	timeval tv;
	float fRet;

	gettimeofday(&tv, NULL);

	if (!timerisset(&lasttv)) memcpy(&lasttv, &tv, sizeof(timeval));

	fRet = (float)((tv.tv_sec - lasttv.tv_sec) * 1000000) + (tv.tv_usec - lasttv.tv_usec);
	fRet /= 1000000.0f;

	memcpy(&lasttv,&tv,sizeof(timeval));

	return fRet;
}

#endif // WIN32

//----------------------------------------------------

void CNetGame::MasterServerAnnounce()
{
	char szPort[256];
	sprintf(szPort, "%i", iListenPort);

#ifdef WIN32
	ShellExecute(0,"open","announce.exe",szPort,NULL,SW_HIDE);
#else
	char szAnnounceCmd[256];
	sprintf(szAnnounceCmd,"./announce %s &",szPort);
	system(szAnnounceCmd);
#endif
}

//----------------------------------------------------

void CNetGame::Process()
{
	float fElapsedTime = GetElapsedTime();

	UpdateNetwork();

	m_pPlayerPool->Process();
	m_pPickUpPool->Process();

	if ((GetCount() - sTime) > count) {
		MasterServerAnnounce();
		sTime = GetCount();
	}

	m_pGameMode->Frame(fElapsedTime);

	if(field_8A3 >= 4) {
		ProcessGameTime();
	}
}

//----------------------------------------------------
// UPDATE NETWORK
//----------------------------------------------------

void CNetGame::UpdateNetwork()
{
	Packet* p;

	while(p=m_pRak->Receive())
	{
		switch(p->data[0]) {
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

void CNetGame::BroadcastData( RakNet::BitStream *bitStream,
							  PacketPriority priority,
							  PacketReliability reliability,
							  char orderingStream,
							  BYTE byteExcludedPlayer )
{
	BYTE x=0;
	int r=0;
	BYTE byteSpectateID=INVALID_ID;
	float fDistance;
	BOOL bShouldSend;
	CPlayer *pPlayer;

	while(x!=MAX_PLAYERS)
	{
		if( (m_pPlayerPool->GetSlotState(x) == TRUE) && 
			(x != byteExcludedPlayer) )
		{
			pPlayer = m_pPlayerPool->GetAt(x);

			if(pPlayer)
			{
				bShouldSend = FALSE;
				byteSpectateID = pPlayer->GetSpectate();
				if(byteSpectateID != INVALID_ID && m_pPlayerPool->GetSlotState(byteSpectateID) == TRUE)
					fDistance = m_pPlayerPool->GetDistanceFromPlayerToPlayer(byteExcludedPlayer, byteSpectateID);
				else
					fDistance = m_pPlayerPool->GetDistanceFromPlayerToPlayer(byteExcludedPlayer, x);

				if(fDistance < 320.0f) {
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
		}
		x++;
	}
}

//----------------------------------------------------
// PACKET HANDLERS
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

void CNetGame::VehicleSync(Packet *p)
{
	// TODO: CNetGame::VehicleSync
}

void CNetGame::PassengerSync(Packet *p)
{
	// TODO: CNetGame::PassengerSync
}

void CNetGame::KickPlayer(BYTE byteKickPlayer)
{
	if (byteKickPlayer < MAX_PLAYERS)
	{
		if (m_pPlayerPool->GetSlotState(byteKickPlayer))
		{
			RakNet::BitStream bs;
			bs.Write(byteKickPlayer);
			m_pRak->RPC("Kicked", &bs, HIGH_PRIORITY, RELIABLE, 0, UNASSIGNED_PLAYER_ID, true, false);

			SetSleep(500);

			m_pPlayerPool->Delete(byteKickPlayer,2);
			m_pRak->Kick(m_pRak->GetPlayerIDFromIndex(byteKickPlayer));
		}
	}
}

void CNetGame::AddBan(char * ip_mask)
{
	m_pRak->AddToBanList(ip_mask);
	
	FILE * fileBanList = fopen("vcmp-svr.banlist","a");
	if(!fileBanList) return;

	fprintf(fileBanList,"%s\n",ip_mask);

	fclose(fileBanList);
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

DWORD CNetGame::GetCount()
{
#ifdef WIN32
	return GetTickCount();
#else
	timeval tv;
	gettimeofday( &tv, NULL );
	return tv.tv_sec + (0.000001f * tv.tv_usec);
#endif
}

void CNetGame::AddSpawn(PLAYER_SPAWN_INFO *pSpawnInfo)
{
	if (m_iSpawnsAvailable < MAX_SPAWNS)
	{
		memcpy(&m_AvailableSpawns[m_iSpawnsAvailable],pSpawnInfo,sizeof(PLAYER_SPAWN_INFO));
		m_iSpawnsAvailable++;
	}
}

void CNetGame::ProcessGameTime()
{
	// TODO: CNetGame::ProcessGameTime
}

//----------------------------------------------------

void CNetGame::SetWepDam(BYTE byteWeaponID, BYTE byteDamage)
{
	m_byteWeaponDamage[byteWeaponID] = byteDamage;

	RakNet::BitStream bsSend;
	bsSend.Write(byteWeaponID);
	bsSend.Write(byteDamage);
	m_pRak->RPC("SetWepDam", &bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_PLAYER_ID, true, false);
}
