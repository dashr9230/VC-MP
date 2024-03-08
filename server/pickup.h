
#pragma once

//----------------------------------------------------

class CPickup
{
public:

	int		m_iPickupID;
	int		m_iPickupType;
	VECTOR	m_vecPos;
	BOOL	m_bIsSpawned;
	int		field_18;

	CPickup(int iType, VECTOR *vecPos);

	void SetID(int iPickupID) { m_iPickupID = iPickupID; };

};

//----------------------------------------------------
