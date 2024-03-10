
#include "game.h"
#include "util.h"
#include "keystuff.h"

extern BYTE byteMapType;

void GameInstallHooks();

//-----------------------------------------------------------

CGame::CGame()
{
	//field_8 = new void[1];
	field_C = 0;
	field_10 = 0;
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

	// Patch to prevent game stopping during a pause
	// (Credits to Luke)
	VirtualProtect((PVOID)0x4D0DA0,7,PAGE_EXECUTE_READWRITE,&dwVP);
	memset((PVOID)0x4D0DA0,0x90,7); // nop * 7
	VirtualProtect((PVOID)0x4D0DA0,7,dwVP,&dwVP2);

	// Patch for GetPlayerTableFromPlayerActor()
	VirtualProtect((PVOID)0x531D40,8,PAGE_EXECUTE_READWRITE,&dwVP);
	memset((PVOID)0x531D40,0x90,8); // nop * 8
	VirtualProtect((PVOID)0x531D40,8,dwVP,&dwVP2);

	// Patch for SetCurrentWeapon fixes fucking FindPlayerPed shit.4FF970
	VirtualProtect((PVOID)0x4FF970,1,PAGE_EXECUTE_READWRITE,&dwVP);
	*(BYTE *)0x4FF970 = 0x9D; // turns mov [eax+.. to mov [ebp+..
	VirtualProtect((PVOID)0x4FF970,1,dwVP,&dwVP2);

	// Player weapon pickups.
	VirtualProtect((PVOID)0x4F6538,1,PAGE_EXECUTE_READWRITE,&dwVP);
	*(BYTE *)0x4F6538 = 0x75;
	VirtualProtect((PVOID)0x4F6538,1,dwVP,&dwVP2);

	// Patch CUserDisplay::Process() to not call CPlacename::Process()
	VirtualProtect((PVOID)0x4D1405,5,PAGE_EXECUTE_READWRITE,&dwVP);
	memset((PVOID)0x4D1405,0x90,5); // nop * 5
	VirtualProtect((PVOID)0x4D1405,5,dwVP,&dwVP2);

	// Patch CPed::RefreshSkin() so that it doesn't try to set any
	// animations 50D96A
	VirtualProtect((PVOID)0x50D96A,5,PAGE_EXECUTE_READWRITE,&dwVP);
	memset((PVOID)0x50D96A,0x90,5); // nop * 5
	VirtualProtect((PVOID)0x50D96A,5,dwVP,&dwVP2);

	// Patch clear weapons to not set armed weapon to fists.4FF767
	VirtualProtect((PVOID)0x4FF767,7,PAGE_EXECUTE_READWRITE,&dwVP);
	memset((PVOID)0x4FF767,0x90,7); // nop * 7
	VirtualProtect((PVOID)0x4FF767,7,dwVP,&dwVP2);

	if(byteMapType == MAP_LIBERTY)
	{
		// Patch to modify the scm path
		VirtualProtect((PVOID)0x6886AC,9,PAGE_EXECUTE_READWRITE,&dwVP);
		strcpy((PCHAR)0x6886AC,"lcmp.scm");
		VirtualProtect((PVOID)0x6886AC,9,dwVP,&dwVP2);

		// Patch to modify the scm path
		VirtualProtect((PVOID)0x6D7368,14,PAGE_EXECUTE_READWRITE,&dwVP);
		strcpy((PCHAR)0x6D7368,"data\\lcmp.scm");
		VirtualProtect((PVOID)0x6D7368,14,dwVP,&dwVP2);
	}
	else if(byteMapType == MAP_VICE)
	{
		VirtualProtect((PVOID)0x4C036C,4,PAGE_EXECUTE_READWRITE,&dwVP);
		*(DWORD *)0x4C036C = 3000;
		VirtualProtect((PVOID)0x4C036C,4,dwVP,&dwVP2);

		VirtualProtect((PVOID)0x4C0309,4,PAGE_EXECUTE_READWRITE,&dwVP);
		*(DWORD *)0x4C0309 = 9000;
		VirtualProtect((PVOID)0x4C0309,4,dwVP,&dwVP2);

		VirtualProtect((PVOID)0x69DB7C,12,PAGE_EXECUTE_READWRITE,&dwVP);
		strcpy((PCHAR)0x69DB7C,"VCMP_W.DAT");
		VirtualProtect((PVOID)0x69DB7C,12,dwVP,&dwVP2);

		VirtualProtect((PVOID)0x68E5A1,9,PAGE_EXECUTE_READWRITE,&dwVP);
		strcpy((PCHAR)0x68E5A1,"VCMP_D.DAT");
		VirtualProtect((PVOID)0x68E5A1,9,dwVP,&dwVP2);

		VirtualProtect((PVOID)0x8614DD,9,PAGE_EXECUTE_READWRITE,&dwVP);
		strcpy((PCHAR)0x8614DD,"VCMP_D.DAT");
		VirtualProtect((PVOID)0x8614DD,9,dwVP,&dwVP2);

		// Patch to modify the scm path
		VirtualProtect((PVOID)0x6886AC,9,PAGE_EXECUTE_READWRITE,&dwVP);
		strcpy((PCHAR)0x6886AC,"vcmp.scm");
		VirtualProtect((PVOID)0x6886AC,9,dwVP,&dwVP2);

		// Patch to modify the scm path
		VirtualProtect((PVOID)0x6D7368,14,PAGE_EXECUTE_READWRITE,&dwVP);
		strcpy((PCHAR)0x6D7368,"data\\vcmp.scm");
		VirtualProtect((PVOID)0x6D7368,14,dwVP,&dwVP2);

		// Patch to modify the loadsc0 txd
		VirtualProtect((PVOID)0x6D5E9C,16,PAGE_EXECUTE_READWRITE,&dwVP);
		strcpy((PCHAR)0x6D5E9C,"ldvcmp0");
		VirtualProtect((PVOID)0x6D5E9C,16,dwVP,&dwVP2);

		VirtualProtect((PVOID)0x68E594,16,PAGE_EXECUTE_READWRITE,&dwVP);
		strcpy((PCHAR)0x68E594,"ldvcmp0");
		VirtualProtect((PVOID)0x68E594,16,dwVP,&dwVP2);

		VirtualProtect((PVOID)0x68E6F4,16,PAGE_EXECUTE_READWRITE,&dwVP);
		strcpy((PCHAR)0x68E6F4,"ldvcmp0");
		VirtualProtect((PVOID)0x68E6F4,16,dwVP,&dwVP2);
	}

	// Patch to increase vehicle pool limit from 110 to 200
	VirtualProtect((PVOID)0x4C02E4,128,PAGE_EXECUTE_READWRITE,&dwVP);
	*(BYTE *)0x4C02E4 = 0x6A;
	*(BYTE *)0x4C02E5 = 0x00; // push 0 (unused param)
	*(BYTE *)0x4C02E6 = 0x68;
	*(BYTE *)0x4C02E7 = 0xC8;
	*(BYTE *)0x4C02E8 = 0x00;
	*(BYTE *)0x4C02E9 = 0x00;
	*(BYTE *)0x4C02EA = 0x00; // push 200
	VirtualProtect((PVOID)0x4C02E4,128,dwVP,&dwVP2);

	// Patch for cAudioManager::GetPedCommentSfx() 5EA1FC
	VirtualProtect((PVOID)0x5EA1FC,1,PAGE_EXECUTE_READWRITE,&dwVP);
	*(BYTE *)0x5EA1FC = 0x75; // jnz
	VirtualProtect((PVOID)0x5EA1FC,1,dwVP,&dwVP2);

	// For passenger engine audio hack (applied later).
	VirtualProtect((PVOID)0x5F2175,2,PAGE_EXECUTE_READWRITE,&dwVP);

	// For 537723 bug (not checking in vehicle)
	VirtualProtect((PVOID)0x537723,2,PAGE_EXECUTE_READWRITE,&dwVP);
	*(BYTE *)0x537723 = 0x90;
	*(BYTE *)0x537724 = 0x90;
	VirtualProtect((PVOID)0x537723,2,dwVP,&dwVP2);

	// For Bike/Passenger bug (test driver for 0)
	VirtualProtect((PVOID)0x5C91F5,4,PAGE_EXECUTE_READWRITE,&dwVP);
	*(BYTE *)0x5C91F5 = 0x85;
	*(BYTE *)0x5C91F6 = 0xC9; // test eax, eax to test ecx, ecx
	*(BYTE *)0x5C91F8 = 0x09; // jz +9 - exit if 0
	VirtualProtect((PVOID)0x5C91F5,4,dwVP,&dwVP2);

	// For Boat driveby bug (test driver for 0)
	VirtualProtect((PVOID)0x5C9558,4,PAGE_EXECUTE_READWRITE,&dwVP);
	*(BYTE *)0x5C9558 = 0x85;
	*(BYTE *)0x5C9559 = 0xC9; // test eax, eax to test ecx, ecx
	*(BYTE *)0x5C955B = 0x09; // jz +9 - exit if 0
	VirtualProtect((PVOID)0x5C9558,4,dwVP,&dwVP2);

	// Hack to prevent replays.
	VirtualProtect((PVOID)0x4A45C3,5,PAGE_EXECUTE_READWRITE,&dwVP);
	memset((PVOID)0x4A45C3,0x90,5); // nop * 5
	VirtualProtect((PVOID)0x4A45C3,5,dwVP,&dwVP2);

	// Hack to get rid of the evasive dive.
	VirtualProtect((PVOID)0x4F6A20,3,PAGE_EXECUTE_READWRITE,&dwVP);
	*(BYTE *)0x4F6A20 = 0xC2u;
	*(BYTE *)0x4F6A21 = 0x08;
	*(BYTE *)0x4F6A22 = 0x00;
	VirtualProtect((PVOID)0x4F6A20,3,dwVP,&dwVP2);

	// Hack to get rid of the weapon pickup message (Tab)
	VirtualProtect((PVOID)0x440B2C,5,PAGE_EXECUTE_READWRITE,&dwVP);
	memset((PVOID)0x440B2C,0x90,5); // nop * 5
	VirtualProtect((PVOID)0x440B2C,5,dwVP,&dwVP2);

	VirtualProtect((PVOID)0x69C780,4,PAGE_EXECUTE_READWRITE,&dwVP);
	*(FLOAT *)0x69C780 = 1200.0f;
	VirtualProtect((PVOID)0x69C780,4,dwVP,&dwVP2);

	VirtualProtect((PVOID)0x487081,6,PAGE_EXECUTE_READWRITE,&dwVP);
	memset((PVOID)0x487081,0x90,6); // nop * 6
	VirtualProtect((PVOID)0x487081,6,dwVP,&dwVP2);

	VirtualProtect((PVOID)0x42BD48,1,PAGE_EXECUTE_READWRITE,&dwVP);
	*(BYTE *)0x42BD48 = 0x90;
	VirtualProtect((PVOID)0x42BD48,1,dwVP,&dwVP2);

	// Install all hooks
	GameInstallHooks();

	GameDisableCheatCodes();

	*(DWORD *)ADDR_MENU = 0;
	*(DWORD *)ADDR_STARTGAME = 1;
}

//-----------------------------------------------------------
