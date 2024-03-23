
#pragma once

//----------------------------------------------------

class CPlayerPool
{
private:
	int field_0[MAX_PLAYERS];
	CLocalPlayer  *m_pLocalPlayer;
	char _gapCC;
	int field_CD[MAX_PLAYERS];
	CHAR	m_szLocalPlayerName[MAX_PLAYER_NAME+1];
	char _gap1AE[2058];

public:

	void SetLocalPlayerName(PCHAR szName) { strcpy(m_szLocalPlayerName,szName); };

	CPlayerPool();
};

//----------------------------------------------------
