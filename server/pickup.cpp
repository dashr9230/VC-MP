
#include "netgame.h"

//----------------------------------------------------------

CPickup::CPickup(int iType, VECTOR *vecPos)
{
	m_iPickupType = iType;
	m_vecPos.X = vecPos->X;
	m_vecPos.Y = vecPos->Y;
	m_vecPos.Z = vecPos->Z;
	m_bIsSpawned = TRUE;
}

//----------------------------------------------------------
