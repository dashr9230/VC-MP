
#pragma once

class CNetGame
{
private:

	CPlayerPool			*m_pPlayerPool;

public:
	CNetGame(PCHAR szHostOrIp,int iPort,PCHAR szPlayerName,PCHAR szPass);
};

//----------------------------------------------------
