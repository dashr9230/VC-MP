
#pragma once

#include "main.h"
#include "player.h"
#include "playerpool.h"
#include "vehicle.h"
#include "vehiclepool.h"
#include "pickup.h"
#include "pickuppool.h"
#include "netrpc.h"
#include "gamemode/generic.h"

//----------------------------------------------------

class CNetGame
{
private:

	CPlayerPool					*m_pPlayerPool;
	CVehiclePool				*m_pVehiclePool;
	CPickUpPool					*m_pPickUpPool;
	RakServerInterface			*m_pRak;
	CGameModeGeneric			*m_pGameLogic;
	int							m_iGameState;

	void SetupInitPositions();

public:

	CNetGame(int iMaxPlayers,int iPort,int iGameType,
		char *szPassword,char *szGameFile,
		BYTE byteFriendlyFire,BYTE byteShowOnRadar);

	int GetGameState() { return m_iGameState; };
	CPlayerPool * GetPlayerPool() { return m_pPlayerPool; };
	RakServerInterface * GetRakServer() { return m_pRak; };
	CGameModeGeneric * GetGameLogic() { return m_pGameLogic; };

	void LoadBanList();

	VECTOR		m_vecInitPlayerPos;
	VECTOR		m_vecInitCameraPos;
	VECTOR		m_vecInitCameraLook;
	float		m_WorldBounds[4]; // pos_x neg_x pos_y neg_y
	int			m_iSpawnsAvailable;

	BYTE field_56;

	BYTE field_5B;
	BYTE field_5C;
};

//----------------------------------------------------
