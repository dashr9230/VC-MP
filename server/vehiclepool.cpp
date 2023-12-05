
#include "main.h"

CVehiclePool::CVehiclePool()
{
	for(BYTE byteVehicleID = 0; byteVehicleID != MAX_VEHICLES; byteVehicleID++) {
		m_bVehicleSlotState[byteVehicleID] = FALSE;
		m_pVehicles[byteVehicleID] = NULL;
	}
}

BYTE CVehiclePool::New(BYTE byteVehicleType,
					   VECTOR * vecPos, float fRotation,
					   int iColor1, int iColor2)
{
	int iVehicleID;

	for(iVehicleID=1; iVehicleID != MAX_VEHICLES; iVehicleID++)
	{
		if(m_bVehicleSlotState[iVehicleID] == FALSE) break;
	}

	if(iVehicleID == MAX_VEHICLES) return 0xFF;

	m_pVehicles[iVehicleID] = new CVehicle(byteVehicleType,vecPos,fRotation,iColor1,iColor2);

	if(m_pVehicles[iVehicleID])
	{
		m_pVehicles[iVehicleID]->SetID(iVehicleID);
		m_bVehicleSlotState[iVehicleID] = TRUE;

		return (BYTE)iVehicleID;
	}
	else
	{
		return 0;
	}
}
