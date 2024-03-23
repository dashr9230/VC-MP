
#pragma once

#include "game.h"
#include "aimstuff.h"

//-----------------------------------------------------------

class CPlayerPed
{
public:
	// Constructor/Destructor.
	CPlayerPed();

	PED_TYPE   *m_pPed;
	DWORD		m_dwGTAId;
	char field_8;
	char _gap9[4];
	int field_D;
};

//-----------------------------------------------------------
