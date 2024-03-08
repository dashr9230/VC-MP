
#include "netgame.h"
#include "rcon.h"

extern CNetGame *pNetGame;
extern CRcon	*pRcon;

//----------------------------------------------------

CPlayerPool::CPlayerPool()
{
	BYTE bytePlayerID = 0;
	while(bytePlayerID != MAX_PLAYERS) {
		m_bPlayerSlotState[bytePlayerID] = FALSE;
		m_pPlayers[bytePlayerID] = NULL;
		bytePlayerID++;
	}
}

//----------------------------------------------------

BOOL CPlayerPool::New(BYTE bytePlayerID, PCHAR szPlayerName)
{
	m_pPlayers[bytePlayerID] = new CPlayer();

	if(m_pPlayers[bytePlayerID])
	{
		strcpy(m_szPlayerName[bytePlayerID],szPlayerName);
		m_pPlayers[bytePlayerID]->SetID(bytePlayerID);
		m_bPlayerSlotState[bytePlayerID] = TRUE;
		m_iPlayerScore[bytePlayerID] = 0;
		m_bIsAnAdmin[bytePlayerID] = FALSE;

		// Notify all the other players of a newcommer with
		// a 'ServerJoin' join RPC 
		RakNet::BitStream bsSend;
		bsSend.Write(bytePlayerID);
		bsSend.Write(strlen(szPlayerName));
		bsSend.Write(szPlayerName,strlen(szPlayerName));
		pNetGame->GetRakServer()->RPC("ServerJoin",&bsSend,HIGH_PRIORITY,RELIABLE_ORDERED,0,
			pNetGame->GetRakServer()->GetPlayerIDFromIndex(bytePlayerID),TRUE,FALSE);

		pRcon->ConsolePrintf("[join] %u %s",bytePlayerID,szPlayerName);

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//----------------------------------------------------
