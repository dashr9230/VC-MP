
#include "main.h"

char szGameModeFile[256];

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

	// TODO: CNetGame::CNetGame()
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

	// Setup pickup pool
	if(!m_pPickUpPool) {
		m_pPickUpPool = new CPickUpPool();
	}

	// Setup gamemode
	if(!m_pGameMode) {
		m_pGameMode = new CGameMode();
	}

	field_8A1 = 1;
	field_8A7 = 12;

	// Start the gamemode script.
	m_pGameMode->Load(szGameModeFile);

	// Flag we're in a running state.
	m_iGameState = GAMESTATE_RUNNING;

	// TODO: CNetGame::Init()
}

//----------------------------------------------------

void CNetGame::ShutdownForGameModeRestart()
{

}

//----------------------------------------------------

void CNetGame::Process()
{
	// TODO: CNetGame::Process
}
