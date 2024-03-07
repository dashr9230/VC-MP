
#pragma once

#include "main.h"
#include "playerpool.h"
#include "vehiclepool.h"
#include "pickuppool.h"
#include "netrpc.h"

//----------------------------------------------------

class CNetGame
{
private:

	CPlayerPool					*m_pPlayerPool;
	CVehiclePool				*m_pVehiclePool;
	CPickUpPool					*m_pPickUpPool;
	RakServerInterface			*m_pRak;

public:

	CNetGame(int iMaxPlayers, int iPort, int iGameType,
			 char * szPassword);

	void LoadBanList();
};

//----------------------------------------------------
