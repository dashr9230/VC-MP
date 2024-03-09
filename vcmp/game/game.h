
#pragma once

#include "address.h"
#include "common.h"
#include "playerped.h"

//-----------------------------------------------------------

class CGame
{
public:

	void	StartGame();

	HWND	GetMainWindowHwnd() { return *(HWND *)ADDR_HWND; };

	CGame();

private:
	char _gap0[8];
	int field_8;
	int field_C;
	char field_10;
};

//-----------------------------------------------------------
