
#ifndef VCMPSRV_PICKUP_H
#define VCMPSRV_PICKUP_H

class CPickup
{
private:
	int			m_iPickupID;
	int			m_iType;
	int			m_iAmount;
	VECTOR		m_vecPos;
	BOOL		m_bIsSpawned;
	DWORD		m_dwRespawnTime;

public:
	CPickup(int iType, VECTOR * vecPos, int iAmount);
	~CPickup(){};

	void SetID(int iPickupID) { m_iPickupID = iPickupID; };

	BOOL ValidateSyncData();
	void SpawnForPlayer(BYTE bytePlayerID);
	void Process();
};

#endif
