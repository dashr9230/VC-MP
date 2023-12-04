
#ifndef VCMPSRV_PICKUP_H
#define VCMPSRV_PICKUP_H

class CPickup
{
private:
	char _gap0[12];
	VECTOR m_vecPos;
	int field_18;
	DWORD field_1C;
public:
	void Process();
	void SpawnForPlayer(BYTE bytePlayerID);
	BOOL ValidateSyncData();
};

#endif
