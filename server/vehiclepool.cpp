
#include "main.h"

//----------------------------------------------------

CVehiclePool::CVehiclePool()
{
	// loop through and initialize all net players to null and slot states to false
	for(BYTE byteVehicleID = 0; byteVehicleID != MAX_VEHICLES; byteVehicleID++) {
		m_bVehicleSlotState[byteVehicleID] = FALSE;
		m_pVehicles[byteVehicleID] = NULL;
	}
}

//----------------------------------------------------

CVehiclePool::~CVehiclePool()
{
	for(BYTE byteVehicleID = 0; byteVehicleID != MAX_VEHICLES; byteVehicleID++) {
		Delete(byteVehicleID);
	}
}

//----------------------------------------------------

BYTE CVehiclePool::New(int iVehicleType, VECTOR * vecPos, float fRotation, int iColor1, int iColor2)
{
	int iVehicleID;

	for(iVehicleID=1; iVehicleID != MAX_VEHICLES; iVehicleID++)
	{
		if(m_bVehicleSlotState[iVehicleID] == FALSE) break;
	}

	if(iVehicleID == MAX_VEHICLES) return 0xFF;

	m_pVehicles[iVehicleID] = new CVehicle((BYTE)iVehicleType,vecPos,fRotation,iColor1,iColor2);

	if(m_pVehicles[iVehicleID])
	{
		m_pVehicles[iVehicleID]->SetID(iVehicleID);
		m_bVehicleSlotState[iVehicleID] = TRUE;

		return iVehicleID;
	}
	else
	{
		return 0;
	}
}

//----------------------------------------------------

BOOL CVehiclePool::Delete(BYTE byteVehicleID)
{
	if(!GetSlotState(byteVehicleID) || !m_pVehicles[byteVehicleID])
	{
		return FALSE; // Vehicle already deleted or not used.
	}

	m_bVehicleSlotState[byteVehicleID] = FALSE;
	delete m_pVehicles[byteVehicleID];
	m_pVehicles[byteVehicleID] = NULL;

	RakNet::BitStream bsSend;
	bsSend.Write(byteVehicleID);
	pNetGame->GetRakServer()->RPC("DeleteVehicle",&bsSend,HIGH_PRIORITY,RELIABLE,0,
		UNASSIGNED_PLAYER_ID,true,false);

	return TRUE;
}

//----------------------------------------------------
