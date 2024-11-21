
#include "main.h"

//----------------------------------------------------

CVehicle::CVehicle( BYTE byteModel, VECTOR *vecPos,
				    float fRotation, int iColor1,
				    int iColor2)
{
	// Store the spawn info.
	m_SpawnInfo.byteVehicleType = byteModel;
	m_SpawnInfo.fRotation = fRotation;
	m_SpawnInfo.vecPos.X = vecPos->X;
	m_SpawnInfo.vecPos.Y = vecPos->Y;
	m_SpawnInfo.vecPos.Z = vecPos->Z;
	m_SpawnInfo.iColor1 = iColor1;
	m_SpawnInfo.iColor2 = iColor2;

	// Set the initial pos to spawn pos.
	memset(&m_matWorld,0,sizeof(MATRIX4X4));
	m_matWorld.pos.X = m_SpawnInfo.vecPos.X;
	m_matWorld.pos.Y = m_SpawnInfo.vecPos.Y;
	m_matWorld.pos.Z = m_SpawnInfo.vecPos.Z;

	memset(&m_vecMoveSpeed,0,sizeof(VECTOR));
	memset(&m_vecTurnSpeed,0,sizeof(VECTOR));

	m_bIsActive = TRUE;
	m_bIsWasted = FALSE;
	m_bHasHadUpdate = FALSE;
	m_byteDriverID = INVALID_ID;
	m_fHealth = 1000.0f;
}

//----------------------------------------------------