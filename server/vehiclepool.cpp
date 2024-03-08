
#include "netgame.h"

//----------------------------------------------------

CVehiclePool::CVehiclePool()
{
	BYTE byteVehicleID = 0;
	while(byteVehicleID != MAX_VEHICLES) {
		m_bVehicleSlotState[byteVehicleID] = FALSE;
		m_pVehicles[byteVehicleID] = NULL;
		byteVehicleID++;
	}
}

//----------------------------------------------------

BOOL CVehiclePool::InitialiseFromConfig(CConfig *pConfig)
{
	int iVehicleArrayCount;
	BYTE d=1;

	int iModelID;
	VECTOR vecPos;
	float fRotation;
	int iColor1, iColor2;
	char * szConfigLine;

	iVehicleArrayCount = pConfig->GetConfigArrayCount("VEHICLE");
	iVehicleArrayCount++;

	while((int)d < iVehicleArrayCount) {

		szConfigLine = pConfig->GetConfigEntryAsString("VEHICLE",d);

		sscanf(szConfigLine,"%d%f%f%f%f%d%d",&iModelID,
			&vecPos.X,&vecPos.Y,&vecPos.Z,&fRotation,&iColor1,&iColor2);

		New(d,(BYTE)iModelID,&vecPos,fRotation,iColor1,iColor2);
		d++;
	}

	return TRUE;
}

//----------------------------------------------------

BOOL CVehiclePool::New(BYTE byteVehicleID, BYTE byteVehicleType,
					   VECTOR * vecPos, float fRotation,
					   int iColor1, int iColor2)
{
	m_pVehicles[byteVehicleID] = new CVehicle(byteVehicleType,vecPos,fRotation,iColor1,iColor2);

	if(m_pVehicles[byteVehicleID])
	{
		m_pVehicles[byteVehicleID]->SetID(byteVehicleID);
		m_bVehicleSlotState[byteVehicleID] = TRUE;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//----------------------------------------------------
