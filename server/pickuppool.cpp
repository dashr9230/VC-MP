
#include "main.h"

CPickUpPool::CPickUpPool()
{
	for (int i = 0; i != MAX_PICKUPS; i++)
	{
		m_bPickUpSlotState[i] = FALSE;
		m_pPickups[i] = NULL;
	}
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
