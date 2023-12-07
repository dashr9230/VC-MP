
#pragma pack(1)
typedef struct _GTA_CONTROLSET
{
	DWORD dwFrontPad;
	WORD wKeys1[19];
	DWORD dwFrontPad2;
	WORD wKeys2[19];
	WORD wTurnLeftRightAnalog[10];
	BYTE bytePadding1[138];
	BYTE byteCrouchAnalog[5];
} GTA_CONTROLSET;

//-----------------------------------------------------------

GTA_CONTROLSET *GameGetInternalKeys();
GTA_CONTROLSET *GameGetLocalPlayerKeys();
GTA_CONTROLSET *GameGetPlayerKeys(int iPlayer);

void GameKeyStatesInit();
void GameStoreLocalPlayerKeys();
void GameSetLocalPlayerKeys();
void GameStoreRemotePlayerKeys(int iPlayer, GTA_CONTROLSET *pGcsKeyStates);
void GameResetPlayerKeys(int iPlayer);
void GameResetLocalKeys();

//-----------------------------------------------------------
