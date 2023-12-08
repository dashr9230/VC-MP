
#pragma once

#include "address.h"
#include "common.h"

//-----------------------------------------------------------

class CGame
{
public:

	void	StartGame();

	DWORD	GetD3DDevice() { return *(DWORD *)ADDR_ID3D8DEVICE; };
	void	SetD3DDevice(DWORD pD3DDevice) { *(DWORD *)ADDR_ID3D8DEVICE = pD3DDevice; };
	DWORD	GetD3D() { return *(DWORD *)ADDR_ID3D8DEVICE; };
	HWND	GetMainWindowHwnd() { return *(HWND *)ADDR_HWND; };

	CGame();

private:
	char field_0;
	char field_1;
	float field_2;
	float field_6;
	char field_A;
	char field_B;
	char field_C;
	char field_D;
	char field_E;
	char field_F;
	char field_10;
	char _gap11[12];
	int field_1D;
	int field_21;
	char field_25;
	char _gap26[38];
	int field_4C;
};

//-----------------------------------------------------------
