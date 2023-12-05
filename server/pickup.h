
#ifndef VCMPSRV_PICKUP_H
#define VCMPSRV_PICKUP_H

class CPickup
{
private:
	int			m_iPickupID;
	int			m_iType;
	int			m_iAmount;
	VECTOR		m_vecPos;
	int field_18;
	DWORD field_1C;
public:

	CPickup(int iType, VECTOR *vecPos, int iAmount);

	void SetID(int iPickupID) { m_iPickupID = iPickupID; }

	void Process();
	void SpawnForPlayer(BYTE bytePlayerID);
	BOOL ValidateSyncData();
};

#endif
