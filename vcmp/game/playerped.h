
#pragma once

#include "game.h"
#include "aimstuff.h"

//-----------------------------------------------------------

class CPlayerPed
{
public:

	void SetDrivebyState(int iToggle);

	// Constructor/Destructor.
	CPlayerPed();

	PED_TYPE   *m_pPed;
	DWORD		m_dwGTAId;
	BYTE		m_bytePlayerNumber;

	BYTE _gap9[4];

	DWORD field_D;
	BYTE field_11;
	DWORD field_12;

	BYTE _gap16[4];

	int m_iDriveByState;
};

//-----------------------------------------------------------
