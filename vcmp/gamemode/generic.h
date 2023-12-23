
#pragma once

class CGameModeGeneric
{
private:
	char field_E;
	DWORD field_F;
	DWORD field_13;
public:
	CGameModeGeneric();
	~CGameModeGeneric() {};

	void HandleClassSelection(CLocalPlayer *pLocalPlayer);

	void sub_10022A50();
};

//----------------------------------------------------------
