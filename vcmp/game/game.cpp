
#include "../main.h"
#include "game.h"
#include "util.h"
#include "keystuff.h"
#include "aimstuff.h"

//-----------------------------------------------------------

CGame::CGame()
{
	// TODO: CGame::CGame()
	field_1D = (int)operator new(1u);
	field_21 = 0;
	field_25 = 0;
	field_0 = 0;
	field_A = 0;
	field_B = 0;
	field_C = 0;
	field_D = 0;
	field_E = 0;
	field_F = 0;
	field_4C = 0;
	field_1 = 1;
	field_2 = 0.0080000004f;
	field_6 = 1.0f;
	field_10 = 1;
}

//-----------------------------------------------------------

LONG WINAPI exc_handler(_EXCEPTION_POINTERS* exc_inf);

void CGame::StartGame()
{
	DWORD dwVP, dwVP2;

	InitPlayerPedPtrRecords();
	GameKeyStatesInit();
	GameAimSyncInit();

	SetUnhandledExceptionFilter(exc_handler);

	// TODO: CGame::StartGame()
}

//-----------------------------------------------------------

