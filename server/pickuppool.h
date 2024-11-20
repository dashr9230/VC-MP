
#ifndef VCMPSRV_PICKUPPOOL_H
#define VCMPSRV_PICKUPPOOL_H

class CPickUpPool
{
private:
	BOOL	m_bPickUpSlotState[MAX_PICKUPS];
	CPickup *m_pPickups[MAX_PICKUPS];
public:

	CPickUpPool();

	BOOL New(int iID, int iType, VECTOR *vecPos, int iAmount);
	void Process();
};

#endif
