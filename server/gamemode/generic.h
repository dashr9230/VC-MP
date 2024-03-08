
#include "../main.h"

//----------------------------------------------------

class CGameModeGeneric
{
private:
	char _gap0[4];
	int field_4;
	char _gap8[12300];
	int field_3014;
public:

	int Init();
	int InitAmmu();
	void HandleClientJoin(BYTE bytePlayerID);
	BOOL HandleSpawnClassRequest(BYTE bytePlayerID,int iSpawnType);

	CGameModeGeneric() {
		field_4 = 0;
		field_3014 = 0;
	}
};

//----------------------------------------------------
// EOF
