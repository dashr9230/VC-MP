
#include "../main.h"

extern CGame		 *pGame;

//----------------------------------------------------------

CLocalPlayer::CLocalPlayer()
{
	field_2E = 0;
	m_pPlayerPed = pGame->FindPlayerPed();
	field_32 = 0;
	field_36 = 0;
	field_13E = 0;
	field_140 = GetTickCount();
	field_144 = GetTickCount();
	field_149 = GetTickCount();

	if(m_pPlayerPed) {
		m_pPlayerPed->sub_1000B660(1);
	}
}

//----------------------------------------------------------
