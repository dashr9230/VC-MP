
#ifndef VCMPSRV_VEHICLEPOOL_H
#define VCMPSRV_VEHICLEPOOL_H

class CVehiclePool
{
private:
	BOOL m_bVehicleSlotState[MAX_VEHICLES];
	CVehicle *m_pVehicles[MAX_VEHICLES];
public:
	CVehiclePool();

	BYTE New(BYTE byteVehicleType, VECTOR * vecPos, float fRotation, int iColor1, int iColor2);
};

#endif
