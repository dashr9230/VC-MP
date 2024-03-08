
#include "netgame.h"

extern CConfig *pServerConfig;

//----------------------------------------------------

CPickUpPool::CPickUpPool()
{
	int i=0;
	while(i!=MAX_PICKUPS) {
		m_bPickupSlotState[i] = FALSE;
		m_pPickups[i] = NULL;
		i++;
	}
}

//----------------------------------------------------

int CPickUpPool::InitialiseFromConfig(CConfig *pConfig)
{
	int iPickupArrayCount;
	int i = 1;

	int iType;
	VECTOR vecPos;
	char *szConfigLine;

	iPickupArrayCount = pServerConfig->GetConfigArrayCount("PICKUP");
	iPickupArrayCount++;

	while(i < iPickupArrayCount) {
		szConfigLine = pServerConfig->GetConfigEntryAsString("PICKUP", i);

		sscanf(szConfigLine, "%i %f %f %f", &iType, &vecPos.X, &vecPos.Y, &vecPos.Z);

		New(i, iType, &vecPos);
		i++;
	}

	return i;
}

//----------------------------------------------------

BOOL CPickUpPool::New(int iPickupID, int iPickupType, VECTOR * vecPos)
{
	m_pPickups[iPickupID] = new CPickup(iPickupType, vecPos);

	if(m_pPickups[iPickupID])
	{
		m_pPickups[iPickupID]->SetID(iPickupID);
		m_bPickupSlotState[iPickupID] = TRUE;
	}
	return TRUE;
}

//----------------------------------------------------
