
#pragma once

#define VCMP_SAFECALL __stdcall

void VCMP_SAFECALL GameDisableCheatCodes();
void VCMP_SAFECALL InitPlayerPedPtrRecords();
void VCMP_SAFECALL SetPlayerPedPtrRecord(BYTE bytePlayer, DWORD dwPedPtr);
BYTE VCMP_SAFECALL FindPlayerNumFromPedPtr(DWORD dwPedPtr);
