
#include "main.h"

CPickUpPool::CPickUpPool()
{
	for (int i = 0; i != MAX_PICKUPS; i++)
	{
		m_bPickUpSlotState[i] = FALSE;
		m_pPickups[i] = NULL;
	}
}

BOOL CPickUpPool::New(int iID, int iType, VECTOR *vecPos, int iAmount)
{
	m_pPickups[iID] = new CPickup(iType, vecPos, iAmount);

	if(m_pPickups[iID])
	{
		m_pPickups[iID]->SetID(iID);
		m_bPickUpSlotState[iID] = TRUE;
	}

	return TRUE;
}

void CPickUpPool::Process()
{
	int i=0;

	while(i!=MAX_PICKUPS) {
		if(TRUE == m_bPickUpSlotState[i]) {
			m_pPickups[i]->Process();
		}
		i++;
	}
}
