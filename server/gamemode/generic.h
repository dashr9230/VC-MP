
#include "../main.h"

#define MAX_SPAWNS 100

//----------------------------------------------------

class CGameModeGeneric
{
private:
	BOOL				m_bGameStated;
	int					m_iLastSpawnIssued;
	PLAYER_SPAWN_INFO	m_AvailableSpawns[MAX_SPAWNS];
	
	int					m_iAvailableSpawnCount;
public:

	int Init();
	int InitAmmu();
	void HandleClientJoin(BYTE bytePlayerID);
	BOOL HandleSpawnClassRequest(BYTE bytePlayerID,int iSpawnType);

	CGameModeGeneric() {
		m_iLastSpawnIssued = 0;
		m_iAvailableSpawnCount = 0;
	}
};

//----------------------------------------------------
// EOF
