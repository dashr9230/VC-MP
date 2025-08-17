
#include "main.h"

extern CNetGame *pNetGame;
extern CRcon	*pRcon;

//----------------------------------------------------

CPlayerPool::CPlayerPool()
{
	for(BYTE bytePlayerID = 0; bytePlayerID != MAX_PLAYERS; bytePlayerID++) {
		m_bPlayerSlotState[bytePlayerID] = FALSE;
		field_190[bytePlayerID] = 0;
		m_pPlayers[bytePlayerID] = NULL;
	}
}

//----------------------------------------------------

CPlayerPool::~CPlayerPool()
{
	for(BYTE bytePlayerID = 0; bytePlayerID != MAX_PLAYERS; bytePlayerID++) {
		Delete(bytePlayerID,0);
	}
}

//----------------------------------------------------

BOOL CPlayerPool::New(BYTE bytePlayerID, PCHAR szPlayerName)
{
	if(GetSlotState(bytePlayerID) || m_pPlayers[bytePlayerID] || strlen(szPlayerName) < 1)
	{
		return FALSE; // Player already deleted or not used.
	}

	m_pPlayers[bytePlayerID] = new CPlayer();

	if(m_pPlayers[bytePlayerID])
	{
		strcpy(m_szPlayerName[bytePlayerID],szPlayerName);
		m_pPlayers[bytePlayerID]->SetID(bytePlayerID);
		m_bPlayerSlotState[bytePlayerID] = TRUE;
		field_190[bytePlayerID] = 0;
		m_iPlayerScore[bytePlayerID] = 0;
		m_bIsAnAdmin[bytePlayerID] = FALSE;

		// Notify all the other players of a newcommer with
		// a 'ServerJoin' join RPC 
		RakNet::BitStream bsSend;
		bsSend.Write(bytePlayerID);
		bsSend.Write(strlen(szPlayerName));
		bsSend.Write(szPlayerName,strlen(szPlayerName));
		pNetGame->GetRakServer()->RPC("ServerJoin" ,&bsSend,HIGH_PRIORITY,RELIABLE_ORDERED,0,
			pNetGame->GetRakServer()->GetPlayerIDFromIndex(bytePlayerID),true,false);

		char ip[22];
		WORD port;
		pNetGame->GetRakServer()->GetPlayerIPFromID(pNetGame->GetRakServer()->GetPlayerIDFromIndex(bytePlayerID), ip, &port);
		pRcon->ConsolePrintf("[join] %u %s %s %d", bytePlayerID, szPlayerName, ip, port);

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//----------------------------------------------------

BOOL CPlayerPool::Delete(BYTE bytePlayerID, BYTE byteReason)
{
	if(!GetSlotState(bytePlayerID) || !m_pPlayers[bytePlayerID])
	{
		return FALSE; // Player already deleted or not used.
	}

	pNetGame->GetFilterScripts()->OnPlayerDisconnect(bytePlayerID, byteReason);
	CGameMode *pGameMode = pNetGame->GetGameMode();
	if(pGameMode) {
		pGameMode->OnPlayerDisconnect(bytePlayerID, byteReason);
	}

	m_bPlayerSlotState[bytePlayerID] = FALSE;
	field_190[bytePlayerID] = 0;
	delete m_pPlayers[bytePlayerID];
	m_pPlayers[bytePlayerID] = NULL;

	// Notify all the other players that this client is quiting.
	RakNet::BitStream bsSend;
	bsSend.Write(bytePlayerID);
	bsSend.Write(byteReason);
	pNetGame->GetRakServer()->RPC("ServerQuit" ,&bsSend,HIGH_PRIORITY,RELIABLE_ORDERED,0,
		pNetGame->GetRakServer()->GetPlayerIDFromIndex(bytePlayerID),true,false);

	pRcon->ConsolePrintf("[part] %u %s %u", bytePlayerID, m_szPlayerName[bytePlayerID], byteReason);

	return TRUE;
}

void CPlayerPool::Process()
{
	BYTE bytePlayerID = 0;

	while(bytePlayerID != MAX_PLAYERS) {
		if(TRUE == m_bPlayerSlotState[bytePlayerID]) {
			m_pPlayers[bytePlayerID]->Process();
		}
		bytePlayerID++;
	}
}

