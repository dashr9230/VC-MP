
#ifndef VCMPSRV_PICKUPPOOL_H
#define VCMPSRV_PICKUPPOOL_H

#define MAX_PICKUPS 336

class CPickUpPool
{
private:
	BOOL	m_bPickUpSlotState[MAX_PICKUPS];
	CPickup *m_pPickups[MAX_PICKUPS];
public:

	CPickUpPool();

	void Process();
};

#endif
