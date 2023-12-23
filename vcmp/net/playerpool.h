
#pragma once

//----------------------------------------------------

class CPlayerPool
{
private:
	int field_0[50];
	CLocalPlayer  *m_pLocalPlayer;
	char field_CC;
	int field_CD[50];
	CHAR	m_szLocalPlayerName[MAX_PLAYER_NAME+1];

public:
	void SetLocalPlayerName(PCHAR szName) { strcpy(m_szLocalPlayerName,szName); };
	PCHAR GetLocalPlayerName() { return m_szLocalPlayerName; };

	CLocalPlayer * GetLocalPlayer() { return m_pLocalPlayer; };

	BOOL Delete(BYTE bytePlayerID, BYTE byteReason);

	CPlayerPool();
	~CPlayerPool();
};

//----------------------------------------------------