
#pragma once

#include "address.h"
#include "common.h"
#include "playerped.h"

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
	char _gap0[8];
	int field_8;
	int field_C;
	char field_10;
};

//-----------------------------------------------------------
