
#include "../main.h"
#include "game.h"
#include "util.h"
#include "keystuff.h"
#include "aimstuff.h"

extern BYTE Map;

void GameInstallHooks();

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

DWORD dwPedHealthPatchAddr[] = {
0x42B98C,0x43DA0D,0x440C0E,0x454920,0x454970,0x458132,0x4581C1,
0x45822E,0x45828F,0x466B4A,0x4ABE65,0x4BECC5,0x4BECCB,0x4EA7E1,
0x4EA806,0x4EA8DB,0x4EE3CC,0x4EE4EC,0x4EE64C,0x4EE795,0x4EE892,
0x4F1438,0x4F26B7,0x4F28DB,0x4F3394,0x4F3EE0,0x4F40C0,0x4F505F,
0x4F573A,0x4F6451,0x4F66D8,0x4F6A51,0x4F71B5,0x4FAD18,0x4FB857,
0x4FBAD8,0x4FC59E,0x4FC77C,0x4FCB3A,0x4FCFAC,0x4FCFD5,0x4FDA3D,
0x500B9A,0x500CD9,0x501975,0x505CEC,0x505E40,0x50690A,0x509755,
0x509E1A,0x509FBD,0x50A66D,0x50AD7E,0x50C197,0x50C4AF,0x50CD8B,
0x50DC87,0x50F3A8,0x5101CA,0x517BC4,0x5181A4,0x5189D5,0x51ACD4,
0x51B43F,0x5208F4,0x526345,0x526766,0x5267B1,0x5267C2,0x5267E0,
0x5267EA,0x526804,0x5268C9,0x526946,0x526A15,0x526B38,0x527940,
0x527EFF,0x52A892,0x52A8F1,0x558A4F,0x558A9F,0x558B43,0x5B8AD5,
0x5B8B11,0x5B8B22,0x5B8B3D,0x5B8B5A,0x5B8B9D,0x5B8BB8,0x5D30BE,
0x5D3AC1,0x6077F1,0x6143D4,0x614C1C,0x614C93,0x62FC94 };

DWORD dwPedBodyRollPatchAddr[] = {
0x42B9EB,0x48E1D0,0x48E2BD,0x48E660,0x48E6FF,0x48E844,
0x48EC48,0x48ED04,0x4D4DEF,0x4D4F90,0x4EE318,0x508F1C,
0x508F33,0x50DB89,0x50E14E,0x522880,0x53499D,0x5382C4 };

void RelocatePedHealthOffset()
{
	DWORD oldProt, oldProt2;

	VirtualProtect((LPVOID)0x401000,0x27CE00,PAGE_EXECUTE_READWRITE,&oldProt);

	UINT x=0;
	while(x<97) {
		*(WORD *)dwPedHealthPatchAddr[x] = 1316;
		x++;
	}

	x=0;
	while(x<18) {
		*(WORD *)dwPedBodyRollPatchAddr[x] = 852;
		x++;
	}

	VirtualProtect((LPVOID)0x401000,0x27CE00,oldProt,&oldProt2);
}

//-----------------------------------------------------------

void sub_10001450()
{
	DWORD oldProt, oldProt2;

	VirtualProtect((LPVOID)0x401000,0x27CE00,PAGE_EXECUTE_READWRITE,&oldProt);

	VirtualProtect((LPVOID)0x401000,0x27CE00,oldProt,&oldProt2);
}

//-----------------------------------------------------------
// extern for the exception box

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
	//VirtualProtect((PVOID)0x531D40,8,PAGE_EXECUTE_READWRITE,&dwVP);
	//memset((PVOID)0x531D40,0x90,8); // nop * 8
	//VirtualProtect((PVOID)0x531D40,8,dwVP,&dwVP2);

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

	// Wanted level heat
	VirtualProtect((LPVOID)0x4D2110,512,PAGE_EXECUTE_READWRITE,&dwVP);
	*(BYTE *)0x4D2144 = 0;
	*(BYTE *)0x4D2148 = 0;
	*(WORD *)0x4D214D = 0;
	*(BYTE *)0x4D2174 = 0;
	*(BYTE *)0x4D2178 = 0;
	*(WORD *)0x4D217D = 0;
	*(BYTE *)0x4D21A4 = 0;
	*(BYTE *)0x4D21A8 = 0;
	*(WORD *)0x4D21AD = 0;
	*(BYTE *)0x4D21D4 = 0;
	*(BYTE *)0x4D21D8 = 0;
	*(WORD *)0x4D21DD = 0;
	*(BYTE *)0x4D2201 = 0;
	*(BYTE *)0x4D2205 = 0;
	*(BYTE *)0x4D2225 = 0;
	*(BYTE *)0x4D2229 = 0;
	VirtualProtect((LPVOID)0x4D2110,512,dwVP,&dwVP2);

	// Disable police helis
	VirtualProtect((LPVOID)0x4D1DE0,4,PAGE_EXECUTE_READWRITE,&dwVP);
	*(DWORD *)0x4D1DE0 = 0xC3C031;
	VirtualProtect((LPVOID)0x4D1DE0,4,dwVP,&dwVP2);

	if(Map == MAP_LIBERTY)
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
	else if(Map == MAP_VICE)
	{
		// Increase dummies
		VirtualProtect((LPVOID)0x4C036C,4,PAGE_EXECUTE_READWRITE,&dwVP);
		*(DWORD *)0x4C036C = 3000;
		VirtualProtect((LPVOID)0x4C036C,4,dwVP,&dwVP2);

		// Increase buildings
		VirtualProtect((LPVOID)0x4C0309,4,PAGE_EXECUTE_READWRITE,&dwVP);
		*(DWORD *)0x4C0309 = 9000;
		VirtualProtect((LPVOID)0x4C0309,4,dwVP,&dwVP2);

		VirtualProtect((LPVOID)0x698770,13,PAGE_EXECUTE_READWRITE,&dwVP);
		strcpy((PCHAR)0x698770,"vcmp_prt.cfg");
		VirtualProtect((LPVOID)0x698770,13,dwVP,&dwVP2);

		VirtualProtect((LPVOID)0x68E5A1,9,PAGE_EXECUTE_READWRITE,&dwVP);
		strcpy((PCHAR)0x68E5A1,"vcmp_d.dat");
		VirtualProtect((LPVOID)0x68E5A1,9,dwVP,&dwVP2);

		VirtualProtect((LPVOID)0x8614DD,9,PAGE_EXECUTE_READWRITE,&dwVP);
		strcpy((PCHAR)0x8614DD,"vcmp_d.dat");
		VirtualProtect((LPVOID)0x8614DD,9,dwVP,&dwVP2);

		/* DoDriveByShootings CWeapon::Update call. 5C9817
		VirtualProtect((PVOID)0x5C9817,8,PAGE_EXECUTE_READWRITE,&dwVP);
		memset((PVOID)0x5C9817,0x90,8); // nop * 8
		VirtualProtect((PVOID)0x5C9817,8,dwVP,&dwVP2);*/

		// Patch to modify the scm path
		VirtualProtect((PVOID)0x6886AC,9,PAGE_EXECUTE_READWRITE,&dwVP);
		strcpy((PCHAR)0x6886AC,"vcmp.scm");	
		VirtualProtect((PVOID)0x6886AC,9,dwVP,&dwVP2);

		// Patch to modify the scm path
		VirtualProtect((PVOID)0x6D7368,14,PAGE_EXECUTE_READWRITE,&dwVP);
		strcpy((PCHAR)0x6D7368,"data\\vcmp.scm");	
		VirtualProtect((PVOID)0x6D7368,14,dwVP,&dwVP2);

		/* Patch to modify the gxt path
		VirtualProtect((PVOID)0x69A4B0,256,PAGE_EXECUTE_READWRITE,&dwVP);
		strcpy((PCHAR)0x69A4B0,"vcmp.gxt");
		strcpy((PCHAR)0x69A4C0,"vcmp.gxt");
		strcpy((PCHAR)0x69A4CC,"vcmp.gxt");
		strcpy((PCHAR)0x69A4D8,"vcmp.gxt");
		strcpy((PCHAR)0x69A4E4,"vcmp.gxt");
		VirtualProtect((PVOID)0x69A4B0,256,dwVP,&dwVP2);*/

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

	// Increase EntryInfoNode
	VirtualProtect((LPVOID)0x4C02A6,2,PAGE_EXECUTE_READWRITE,&dwVP);
	*(WORD *)0x4C02A6 = 16000;
	VirtualProtect((LPVOID)0x4C02A6,2,dwVP,&dwVP2);

	// Patch for cAudioManager::GetPedCommentSfx() 5EA1FC
	VirtualProtect((PVOID)0x5EA1FC,1,PAGE_EXECUTE_READWRITE,&dwVP);
	*(BYTE *)0x5EA1FC = 0x75; // jnz
	VirtualProtect((PVOID)0x5EA1FC,1,dwVP,&dwVP2);

	/* ProcessVehicleOneShots (Reverse logic for CPed::IsPlayer()
	VirtualProtect((PVOID)0x5EB6CD,1,PAGE_EXECUTE_READWRITE,&dwVP);
	*(BYTE *)0x5EB6CD = 0x85; // jnz
	VirtualProtect((PVOID)0x5EB6CD,1,dwVP,&dwVP2);*/

	/* For passenger engine audio hack (applied later).
	VirtualProtect((PVOID)0x5F2175,2,PAGE_EXECUTE_READWRITE,&dwVP);*/

	VirtualProtect((LPVOID)0x5B49A8,1,PAGE_EXECUTE_READWRITE,&dwVP);
	*(BYTE *)0x5B49A8 = 60;
	VirtualProtect((LPVOID)0x5B49A8,1,dwVP,&dwVP2);

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
	*(BYTE *)0x4F6A20 = 0xC2;
	*(BYTE *)0x4F6A21 = 0x08;
	*(BYTE *)0x4F6A22 = 0x00;
	VirtualProtect((PVOID)0x4F6A20,3,dwVP,&dwVP2);

	// Hack to get rid of the weapon pickup message (Tab)
	VirtualProtect((PVOID)0x440B2C,5,PAGE_EXECUTE_READWRITE,&dwVP);
	memset((PVOID)0x440B2C,0x90,5); // nop * 5
	VirtualProtect((PVOID)0x440B2C,5,dwVP,&dwVP2);

	VirtualProtect((LPVOID)0x5379B2,1,PAGE_EXECUTE_READWRITE,&dwVP);
	*(BYTE *)0x5379B2 = 0;
	VirtualProtect((LPVOID)0x5379B2,1,dwVP,&dwVP2);

	// Mute some ped sound
	VirtualProtect((LPVOID)0x5379BD,3,PAGE_EXECUTE_READWRITE,&dwVP);
	*(BYTE *)0x5379BD = 0;
	VirtualProtect((LPVOID)0x5379BD,3,dwVP,&dwVP2);

	// Disable pad shake
	VirtualProtect((LPVOID)0x5CC92B,1,PAGE_EXECUTE_READWRITE,&dwVP);
	*(BYTE *)0x5CC92B = 0xEB;
	VirtualProtect((LPVOID)0x5CC92B,1,dwVP,&dwVP2);

	VirtualProtect((LPVOID)0x69C780,4,PAGE_EXECUTE_READWRITE,&dwVP);
	*(FLOAT *)0x69C780 = 1200.0f;
	VirtualProtect((LPVOID)0x69C780,4,dwVP,&dwVP2);

	// Disable time passing
	VirtualProtect((LPVOID)0x487081,6,PAGE_EXECUTE_READWRITE,&dwVP);
	memset((PVOID)0x487081,0x90,6);
	VirtualProtect((LPVOID)0x487081,6,dwVP,&dwVP2);

	VirtualProtect((LPVOID)0x42BD48,1,PAGE_EXECUTE_READWRITE,&dwVP);
	*(BYTE *)0x42BD48 = 0x90;
	VirtualProtect((LPVOID)0x42BD48,1,dwVP,&dwVP2);

	VirtualProtect((LPVOID)0x628EFF,2,PAGE_EXECUTE_READWRITE,&dwVP);
	*(BYTE *)0x628EFF = 0xEB;
	*(BYTE *)0x628E00 = 0x05;
	VirtualProtect((LPVOID)0x628EFF,2,dwVP,&dwVP2);

	VirtualProtect((LPVOID)0x58CD4E,6,PAGE_EXECUTE_READWRITE,&dwVP);
	memset((PVOID)0x58CD4E,0x90,6);
	VirtualProtect((LPVOID)0x58CD4E,6,dwVP,&dwVP2);

	// Install all hooks
	GameInstallHooks();

	RelocatePedHealthOffset();

	GameDisableCheatCodes();

	// TODO: CGame::StartGame()
}

//-----------------------------------------------------------

