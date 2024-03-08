
#pragma once

//----------------------------------------------------

class CVehiclePool
{
private:

	BOOL m_bVehicleSlotState[MAX_VEHICLES];
	CVehicle *m_pVehicles[MAX_VEHICLES];

public:

	CVehiclePool();

	BOOL New(BYTE byteVehicleID, BYTE byteVehicleType, VECTOR * vecPos, float fRotation, int iColor1, int iColor2);

	BOOL InitialiseFromConfig(CConfig *pConfig);

};

//----------------------------------------------------
