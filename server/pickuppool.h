
#pragma once

//----------------------------------------------------

class CPickUpPool
{
private:
	BOOL	m_bPickupSlotState[MAX_PICKUPS];
	CPickup	*m_pPickups[MAX_PICKUPS];

public:

	CPickUpPool();

	BOOL New(int iPickupID, int iPickupType, VECTOR * vecPos);

	int InitialiseFromConfig(CConfig *pConfig);
};

//----------------------------------------------------
