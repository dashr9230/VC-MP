
#ifndef VCMPSRV_PLAYERPOOL_H
#define VCMPSRV_PLAYERPOOL_H

#define INVALID_PLAYER_ID 255

class CPlayerPool
{
private:

	BOOL	m_bPlayerSlotState[MAX_PLAYERS];
	CPlayer *m_pPlayers[MAX_PLAYERS];
	int field_190[MAX_PLAYERS];
	CHAR	m_szPlayerName[MAX_PLAYERS][MAX_PLAYER_NAME+1];
	int 	m_iPlayerScore[MAX_PLAYERS];
	int		m_iPlayerMoney[MAX_PLAYERS];
	BOOL	m_bIsAnAdmin[MAX_PLAYERS];

public:

	CPlayerPool();
	~CPlayerPool();

	void Process();
	BOOL Delete(BYTE bytePlayerID, BYTE byteReason);
	BOOL New(BYTE bytePlayerID, PCHAR szPlayerName);

	// Find out if the slot is inuse.
	BOOL GetSlotState(BYTE bytePlayerID) {
		if(bytePlayerID > MAX_PLAYERS) { return FALSE; }
		return m_bPlayerSlotState[bytePlayerID];
	};

	PCHAR GetPlayerName(BYTE bytePlayerID) {
		if(bytePlayerID >= MAX_PLAYERS) { return FALSE; }
		return m_szPlayerName[bytePlayerID];
	};

	void ResetPlayerScoresAndMoney() {
		memset(&m_iPlayerScore[0],0,sizeof(int) * MAX_PLAYERS);
		memset(&m_iPlayerMoney[0],0,sizeof(int) * MAX_PLAYERS);
	};

};

#endif
