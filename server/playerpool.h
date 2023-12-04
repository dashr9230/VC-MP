
#ifndef VCMPSRV_PLAYERPOOL_H
#define VCMPSRV_PLAYERPOOL_H

#define INVALID_PLAYER_ID 255

class CPlayerPool
{
private:

	BOOL	m_bPlayerSlotState[MAX_PLAYERS];
	CPlayer *m_pPlayers[MAX_PLAYERS];
	int		field_190[MAX_PLAYERS];

	int 	m_iPlayerScore[MAX_PLAYERS];
	int		m_iPlayerMoney[MAX_PLAYERS];

public:

	CPlayerPool();
	~CPlayerPool();

	void Process();
	BOOL Delete(BYTE bytePlayerID, BYTE byteReason);

	void ResetPlayerScoresAndMoney() {
		memset(&m_iPlayerScore[0],0,sizeof(int) * MAX_PLAYERS);
		memset(&m_iPlayerMoney[0],0,sizeof(int) * MAX_PLAYERS);
	};

};

#endif
