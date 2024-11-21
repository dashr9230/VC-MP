
#ifndef VCMPSRV_VEHICLE_H
#define VCMPSRV_VEHICLE_H

typedef struct _VEHICLE_SPAWN_INFO
{
	BYTE byteVehicleType;
	VECTOR vecPos;
	float fRotation;
	int iColor1;
	int iColor2;
} VEHICLE_SPAWN_INFO;

//----------------------------------------------------

class CVehicle
{
public:
	BYTE					m_byteVehicleID;
	BYTE					m_byteDriverID;
	BYTE					m_bytePassengers[7];
	BOOL					m_bIsActive;
	BOOL					m_bIsWasted;
	VEHICLE_SPAWN_INFO		m_SpawnInfo;
	MATRIX4X4				m_matWorld;
	VECTOR					m_vecMoveSpeed;
	VECTOR					m_vecTurnSpeed;
	float					m_fHealth;
	BOOL					m_bHasHadUpdate;

	CVehicle(BYTE byteModel,VECTOR *vecPos,float fRotation,int iColor1,int iColor2);
	~CVehicle(){};

	BOOL IsActive() { return m_bIsActive; };

	void SetID(BYTE byteVehicleID) { m_byteVehicleID = byteVehicleID; };
	VEHICLE_SPAWN_INFO * GetSpawnInfo() { return &m_SpawnInfo; };
};

#endif
