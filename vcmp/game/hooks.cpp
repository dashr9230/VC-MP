
#include "../main.h"

#define NUDE void _declspec(naked)

//-----------------------------------------------------------

BYTE PreGameProcess_HookJmpCode[]	= {0xFF,0x25,0x77,0x5D,0x4A,0x00}; //4A5D77
BYTE PedSetObjective_HookJmpCode[]	= {0xFF,0x25,0x75,0x11,0x40,0x00,0x90,0x90,0x90};
BYTE RadarTranslateColor_HookJmpCode[] = {0xFF,0x25,0x44,0x30,0x4C,0x00,0x90}; // 4C3044
BYTE EnterCarAnimCallback_HookJmpCode[] = {0xFF,0x25,0xD8,0x28,0x51,0x00,0x90,0x90}; // 5128D8
BYTE HookedRand_HookJmpCode[] = {0xFF,0x25,0xE8,0x99,0x64,0x00,0x90,0x90}; // 6499E8
BYTE InflictDamage_HookJmpCode[] = {0xFF,0x25,0x15,0x5B,0x52,0x00}; // 525B15
BYTE InTheGame_HookJmpCode[] = {0xFF,0x25,0x3c,0x5c,0x4a,0x00}; //4A5C3C

//-----------------------------------------------------------

NUDE PreGameProcessHook() {} // TODO: PreGameProcessHook
NUDE InTheGameHook() {} // TODO: InTheGameHook
NUDE CPlayerPed_ProcessControl_Hook() {} // TODO: CPlayerPed_ProcessControl_Hook
NUDE CBike_ProcessControl_Hook() {} // TODO: CBike_ProcessControl_Hook
NUDE CBoat_ProcessControl_Hook() {} // TODO: CBoat_ProcessControl_Hook
NUDE CAutomobile_ProcessControl_Hook() {} // TODO: CAutomobile_ProcessControl_Hook
NUDE RadarTranslateColor() {} // TODO: RadarTranslateColor
NUDE HookedRand_Hook() {} // TODO: HookedRand_Hook
NUDE EnterCarAnimCallback_Hook() {} // TODO: EnterCarAnimCallback_Hook
NUDE CPed_InflictDamageHook() {} // TODO: CPed_InflictDamageHook

//-----------------------------------------------------------

void InstallMethodHook(DWORD dwInstallAddress,DWORD dwHookFunction)
{
	DWORD dwVP, dwVP2;
	VirtualProtect((LPVOID)dwInstallAddress,4,PAGE_EXECUTE_READWRITE,&dwVP);
	*(PDWORD)dwInstallAddress = (DWORD)dwHookFunction;
	VirtualProtect((LPVOID)dwInstallAddress,4,dwVP,&dwVP2);
}

//-----------------------------------------------------------

void InstallHook( DWORD dwInstallAddress,
				  DWORD dwHookFunction,
				  DWORD dwHookStorage,
				  BYTE * pbyteJmpCode,
				  int iJmpCodeSize )
{
	DWORD dwVP, dwVP2;

	// Install the pointer to procaddr.
	VirtualProtect((PVOID)dwHookStorage,4,PAGE_EXECUTE_READWRITE,&dwVP);
	*(PDWORD)dwHookStorage = (DWORD)dwHookFunction;
	VirtualProtect((PVOID)dwHookStorage,4,dwVP,&dwVP2);

	// Install the Jmp code.
	VirtualProtect((PVOID)dwInstallAddress,iJmpCodeSize,PAGE_EXECUTE_READWRITE,&dwVP);
	memcpy((PVOID)dwInstallAddress,pbyteJmpCode,iJmpCodeSize);
	VirtualProtect((PVOID)dwInstallAddress,iJmpCodeSize,dwVP,&dwVP2);
}

//-----------------------------------------------------------

void GameInstallHooks()
{
	InstallHook(0x6499F0,(DWORD)HookedRand_Hook,0x6499E8,HookedRand_HookJmpCode,
		sizeof(HookedRand_HookJmpCode));

	// Below is the Render2DStuff hook, don't be confused by the poor naming.
	InstallHook(ADDR_PRE_GAME_PROCESS,(DWORD)PreGameProcessHook,
		ADDR_PRE_GAME_PROCESS_STORAGE,PreGameProcess_HookJmpCode,
		sizeof(PreGameProcess_HookJmpCode));

	InstallHook(0x4A5BE0,(DWORD)InTheGameHook,0x4A5C3C,InTheGame_HookJmpCode,
		sizeof(InTheGame_HookJmpCode));

	// Install CPlayerPed::ProcessControl hook.
	InstallMethodHook(0x694D90,(DWORD)CPlayerPed_ProcessControl_Hook);

	// Install CBike::ProcessControl hook.
	InstallMethodHook(0x6D7B54,(DWORD)CBike_ProcessControl_Hook);

	// Install CBoat::ProcessControl hook.
	InstallMethodHook(0x69B0D4,(DWORD)CBoat_ProcessControl_Hook);

	// Install CAutomobile::ProcessControl hook.
	InstallMethodHook(0x69ADB0,(DWORD)CAutomobile_ProcessControl_Hook);

	// Install Hook for RadarTranslateColor
	InstallHook(0x4C3050,(DWORD)RadarTranslateColor,0x4C3044,
		RadarTranslateColor_HookJmpCode,sizeof(RadarTranslateColor_HookJmpCode));

	InstallHook(0x525B20,(DWORD)CPed_InflictDamageHook,0x525B15,
		InflictDamage_HookJmpCode,sizeof(InflictDamage_HookJmpCode));

	// Install Hook for enter car animation callback..
	// Update: Causing even more problems.
	InstallHook(0x5128E0,(DWORD)EnterCarAnimCallback_Hook,0x5128D8,
		EnterCarAnimCallback_HookJmpCode,sizeof(EnterCarAnimCallback_HookJmpCode));
}

//-----------------------------------------------------------
