
#ifndef VCMPSRV_VEHICLE_H
#define VCMPSRV_VEHICLE_H

class CVehicle
{
public:

	BYTE				m_byteVehicleID;

	BOOL					m_bIsActive;

	CVehicle(BYTE byteModel,VECTOR *vecPos,float fRotation,int iColor1,int iColor2);

	BOOL IsActive() { return m_bIsActive; };

	void SetID(BYTE byteVehicleID) { m_byteVehicleID = byteVehicleID; };
};

#endif
