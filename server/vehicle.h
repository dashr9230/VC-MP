
#pragma once

//----------------------------------------------------

class CVehicle
{
public:

	BYTE					m_byteVehicleID;

	CVehicle(BYTE byteModel,VECTOR *vecPos,float fRotation,int iColor1,int iColor2);

	void SetID(BYTE byteVehicleID) { m_byteVehicleID = byteVehicleID; };
};

//----------------------------------------------------
