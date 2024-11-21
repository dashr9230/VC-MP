
#ifndef VCMPSRV_VEHICLEPOOL_H
#define VCMPSRV_VEHICLEPOOL_H

class CVehiclePool
{
private:
	BOOL m_bVehicleSlotState[MAX_VEHICLES];
	CVehicle *m_pVehicles[MAX_VEHICLES];

public:
	CVehiclePool();
	~CVehiclePool();

	BYTE New(int iVehicleType, VECTOR * vecPos, float fRotation, int iColor1, int iColor2);
	BOOL Delete(BYTE byteVehicleID);

	// Find out if the slot is inuse.
	BOOL GetSlotState(BYTE byteVehicleID)
	{
		if(byteVehicleID > MAX_VEHICLES) { return FALSE; }
		return m_bVehicleSlotState[byteVehicleID];
	};
};

#endif
