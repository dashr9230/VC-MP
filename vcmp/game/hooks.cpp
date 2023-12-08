
#include "../main.h"
#include "util.h"

extern DWORD dwGameLoop;

#define NUDE void _declspec(naked)

//-----------------------------------------------------------

PED_TYPE	*_pPlayer;

DWORD	dwStackFrame;
int		iRadarColor1=0;
BYTE	*pbyteCameraMode = (BYTE *)0x7E481C;
BYTE	*pbyteCurrentPlayer = (BYTE *)0xA10AFB;

//-----------------------------------------------------------

BYTE PreGameProcess_HookJmpCode[]	= {0xFF,0x25,0x77,0x5D,0x4A,0x00}; //4A5D77
BYTE PedSetObjective_HookJmpCode[] = {0xFF,0x25,0x75,0x11,0x40,0x00,0x90,0x90,0x90};
BYTE RadarTranslateColor_HookJmpCode[] = {0xFF,0x25,0x44,0x30,0x4C,0x00,0x90}; // 4C3044
BYTE EnterCarAnimCallback_HookJmpCode[] = {0xFF,0x25,0xD8,0x28,0x51,0x00,0x90,0x90}; // 5128D8
BYTE HookedRand_HookJmpCode[] = {0xFF,0x25,0xE8,0x99,0x64,0x00,0x90,0x90}; // 6499E8
BYTE InflictDamage_HookJmpCode[] = {0xFF,0x25,0x15,0x5B,0x52,0x00}; // 525B15
BYTE InTheGame_HookJmpCode[] = {0xFF,0x25,0x3C,0x5C,0x4A,0x00}; //4A5C3C
BYTE UNK_1_HookJmpCode[] = {0xFF,0x25,0x72,0x13,0x40,0x00,0x90,0x90};
BYTE UNK_2_HookJmpCode[] = {0xFF,0x25,0x06,0xDD,0x67,0x00,0x90};

//-----------------------------------------------------------

NUDE HOOK_1() { } // TODO
NUDE HOOK_2() { } // TODO
NUDE HOOK_4() { } // TODO
NUDE HOOK_5() { } // TODO
NUDE HOOK_6() { } // TODO
NUDE CPlayerPed_ProcessControl_Hook() { } // TODO: CPlayerPed_ProcessControl_Hook
NUDE CBike_ProcessControl_Hook() { } // TODO: CBike_ProcessControl_Hook
NUDE CBoat_ProcessControl_Hook() { } // TODO: CBoat_ProcessControl_Hook
NUDE CAutomobile_ProcessControl_Hook() { } // TODO: CAutomobile_ProcessControl_Hook
NUDE CPed_InflictDamageHook() { } // TODO: CPed_InflictDamageHook

void DoCheatEntryChecking()
{

}

//-----------------------------------------------------------

void DoCheatExitStoring()
{

}

//-----------------------------------------------------------

NUDE PreGameProcessHook()
{
	_asm mov dwStackFrame, esp
	_asm pushad

	_asm mov edx, dwGameLoop ; upcalls our main game loop handler
	_asm call edx

	DoCheatExitStoring();

	_asm popad

	_asm mov esp, dwStackFrame
	_asm push ebx
	_asm sub esp, 112
	_asm push 0
	_asm mov edx, ADDR_PRE_GAME_PROCESS ; back into the real proc
	_asm add edx, 6
	_asm jmp edx
}

//-----------------------------------------------------------

NUDE InTheGameHook()
{
	_asm pushad

	DoCheatEntryChecking();

	_asm popad

	_asm mov edx, 0x4A5D80
	_asm call edx
	_asm pop ecx

	_asm mov edx, 0x4A5BE6
	_asm jmp edx
}

//-----------------------------------------------------------

void _stdcall DoEnterVehicleNotification(BOOL bPassenger)
{
	/*
	if(pNetGame) {
		ObjectiveVehicle = (VEHICLE_TYPE *)_pVehicle;
		pNetGame->GetPlayerPool()->GetLocalPlayer()
			->SendEnterVehicleNotification(pNetGame->GetVehiclePool()
			->FindIDFromGtaPtr(ObjectiveVehicle),bPassenger);
	}*/
}

//-----------------------------------------------------------

void _stdcall DoExitVehicleNotification()
{
	/*
	if(pNetGame) {
		ObjectiveVehicle = (VEHICLE_TYPE *)_pVehicle;
		if(ObjectiveVehicle->pDriver != GamePool_FindPlayerPed()) {
			pNetGame->GetPlayerPool()->GetLocalPlayer()
					->SendExitVehicleNotification(pNetGame->GetVehiclePool()
					->FindIDFromGtaPtr(ObjectiveVehicle));
		}
	}*/
}

//-----------------------------------------------------------
// Hooks CPed::SetObjective(enum eObjective)

NUDE CPed_SetObjective_Hook()
{

}

//-----------------------------------------------------------

NUDE RadarTranslateColor()
{
	_asm mov eax, [esp+4]
	_asm mov iRadarColor1, eax
	TranslateColorCodeToRGBA(iRadarColor1); // return will still be in eax.
	_asm ret
}

//-----------------------------------------------------------

NUDE CantFindFuckingAnim()
{
	_asm mov eax, [esp+4]
	_asm test eax, eax
	_asm jnz its_ok

	_asm ret ; was 0, so foobarred

its_ok:

	_asm mov edx, 0x405AC0
	_asm add edx, 4

}

//-----------------------------------------------------------
// ok, this bullshit procedure don't check the fucking
// vehicle pointer for 0 and caused the widely hated 5128fb crash.

NUDE EnterCarAnimCallback_Hook()
{
	_asm mov edx, [esp+4]
	_asm mov eax, [esp+8]

	_asm mov _pPlayer, eax
	_asm pushad

	if( _pPlayer->pVehicle == 0 &&
		_pPlayer != GamePool_FindPlayerPed()) {
		_asm popad
		_asm ret
	}

	_asm popad
	_asm mov ebx, 0x5128E0
	_asm add ebx, 8
	_asm jmp ebx
}

//-----------------------------------------------------------
// The rand() function in GTA is hooked and we can
// control the seed this way.

NUDE HookedRand_Hook()
{
	rand();
	_asm ret
}

//-----------------------------------------------------------

NUDE HOOK_3() // TODO: Rename HOOK_3
{
	_asm mov eax, [esp+112]
	_asm mov [ebx+1287], al
	_asm mov ecx, ebx
	_asm mov eax, 0x4F4930
	_asm call eax

	_asm mov ecx, 0x525CB9
	_asm jmp ecx
}






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

void InstallJumpHook(DWORD dwInstallAddress, DWORD dwHookFunction, DWORD dwHookStorage)
{
	DWORD dwVP, dwVP2;

	VirtualProtect((PVOID)dwHookStorage,4,PAGE_EXECUTE_READWRITE,&dwVP);
	*(PDWORD)dwHookStorage = (DWORD)dwHookFunction;
	VirtualProtect((PVOID)dwHookStorage,4,dwVP,&dwVP2);

	VirtualProtect((LPVOID)dwInstallAddress,6,PAGE_EXECUTE_READWRITE,&dwVP);
	*(PWORD)(dwInstallAddress) = 0x25FF;
	*(PDWORD)(dwInstallAddress+2) = (DWORD)dwHookStorage;
	VirtualProtect((LPVOID)dwInstallAddress,6,dwVP,&dwVP2);
}

//-----------------------------------------------------------

void RemoveJumpHook(DWORD dwInstallAddress, DWORD dwOrig, WORD wOrig, DWORD dwHookStorage)
{
	DWORD dwVP, dwVP2;

	VirtualProtect((PVOID)dwHookStorage,4,PAGE_EXECUTE_READWRITE,&dwVP);
	*(PDWORD)dwHookStorage = 0;
	VirtualProtect((PVOID)dwHookStorage,4,dwVP,&dwVP2);

	VirtualProtect((LPVOID)dwInstallAddress,6,PAGE_EXECUTE_READWRITE,&dwVP);
	*(PDWORD)(dwInstallAddress) = (DWORD)dwOrig;
	*(PWORD)(dwInstallAddress+4) = (WORD)wOrig;
	VirtualProtect((LPVOID)dwInstallAddress,6,dwVP,&dwVP2);
}

//-----------------------------------------------------------

void GameInstallHooks()
{
	InstallJumpHook(0x4506DC,(DWORD)HOOK_1,0x450C78);
	InstallJumpHook(0x4D75B8,(DWORD)HOOK_2,0x4D74FC);
	InstallJumpHook(0x525CB2,(DWORD)HOOK_3,0x526B94);
	InstallJumpHook(0x4F65C0,(DWORD)HOOK_4,0x4F6A17);
	InstallJumpHook(0x5B8370,(DWORD)HOOK_5,0x5B843A);
	InstallJumpHook(0x531D40,(DWORD)HOOK_6,0x531D54);

	InstallHook(0x6499F0,(DWORD)HookedRand_Hook,0x6499E8,HookedRand_HookJmpCode,
		sizeof(HookedRand_HookJmpCode));

	// Below is the Render2DStuff hook, don't be confused by the poor naming.
	InstallHook(0x4A6190,(DWORD)PreGameProcessHook,
		0x4A5D77,PreGameProcess_HookJmpCode,
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
