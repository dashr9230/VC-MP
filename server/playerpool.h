
#pragma once

#define INVALID_PLAYER_ID 255

//----------------------------------------------------

class CPlayerPool
{
private:

	BOOL	m_bPlayerSlotState[MAX_PLAYERS];
	CPlayer *m_pPlayers[MAX_PLAYERS];
	CHAR	m_szPlayerName[MAX_PLAYERS][MAX_PLAYER_NAME+1];
	int		m_iPlayerScore[MAX_PLAYERS];
	BOOL	m_bIsAnAdmin[MAX_PLAYERS];

public:

	CPlayerPool();

	BOOL New(BYTE bytePlayerID, PCHAR szPlayerName);

	// Retrieve a player
	CPlayer* GetAt(BYTE bytePlayerID) {
		if(bytePlayerID > MAX_PLAYERS) { return NULL; }
		return m_pPlayers[bytePlayerID];
	};

	void SetAdmin(BYTE bytePlayerID) { m_bIsAnAdmin[bytePlayerID] = TRUE; };
};

//----------------------------------------------------
