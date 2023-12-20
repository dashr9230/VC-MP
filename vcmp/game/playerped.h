
#pragma once

#include "game.h"

//-----------------------------------------------------------

class CPlayerPed
{
public:

	void sub_1000B660(int a2);

	// Constructor/Destructor.	
	CPlayerPed();

	PED_TYPE   *m_pPed;
	DWORD		m_dwGTAId;
	BYTE		m_bytePlayerNumber;
	char _gap8[5];
	int field_D;
	char field_11;
	int field_12;
	char _gap16[4];
	int field_1A;
};

//-----------------------------------------------------------
