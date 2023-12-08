
#pragma once

#define VCMP_SAFECALL __stdcall

int VCMP_SAFECALL GameGetWeaponModelFromWeapon(int iWeaponID);
void VCMP_SAFECALL GameDisableCheatCodes();
PED_TYPE * VCMP_SAFECALL GamePool_Ped_GetAt(int iID);
int VCMP_SAFECALL GamePool_Ped_GetIndex(PED_TYPE *pPed);
VEHICLE_TYPE * VCMP_SAFECALL GamePool_Vehicle_GetAt(int iID);
int VCMP_SAFECALL GamePool_Vehicle_GetIndex(VEHICLE_TYPE *pVehicle);
PED_TYPE * VCMP_SAFECALL GamePool_FindPlayerPed();
DWORD VCMP_SAFECALL TranslateColorCodeToRGBA(int iCode);
BOOL VCMP_SAFECALL GameIsEntityOnScreen(DWORD * pdwEnt);
void VCMP_SAFECALL InitPlayerPedPtrRecords();
void VCMP_SAFECALL SetPlayerPedPtrRecord(BYTE bytePlayer, DWORD dwPedPtr);
BYTE VCMP_SAFECALL FindPlayerNumFromPedPtr(DWORD dwPedPtr);

//-----------------------------------------------------------
