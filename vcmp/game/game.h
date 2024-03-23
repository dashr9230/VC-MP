
#pragma once

#include "address.h"
#include "common.h"
#include "playerped.h"

//-----------------------------------------------------------

class CGame
{
public:
	int field_0;
	int field_4;

	void	StartGame();

	DWORD	GetD3DDevice() { return *(DWORD *)ADDR_ID3D8DEVICE; };
	void	SetD3DDevice(DWORD pD3DDevice) { *(DWORD *)ADDR_ID3D8DEVICE = pD3DDevice; };
	DWORD	GetD3D() { return *(DWORD *)ADDR_ID3D8DEVICE; };
	HWND	GetMainWindowHwnd() { return *(HWND *)ADDR_HWND; };

	//-----------------------------------------------------------

	CPlayerPed  *FindPlayerPed() {
		if(m_pInternalPlayer==NULL)	m_pInternalPlayer = new CPlayerPed();
		return m_pInternalPlayer;
	};

	//-----------------------------------------------------------

	CGame();

private:
	int field_8;
	CPlayerPed		*m_pInternalPlayer;
	char field_10;
};

//-----------------------------------------------------------
