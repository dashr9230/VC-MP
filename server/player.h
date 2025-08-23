
#ifndef VCMPSRV_PLAYER_H
#define VCMPSRV_PLAYER_H

#define UPDATE_TYPE_NONE		0

#pragma pack(1)
typedef struct _PLAYER_SPAWN_INFO
{
	BYTE byteTeam;
	BYTE byteSkin;
	VECTOR vecPos;
	float fRotation;
	int iSpawnWeapons[3];
	int iSpawnWeaponsAmmo[3];
} PLAYER_SPAWN_INFO;

class CPlayer
{
private:

	BYTE					m_bytePlayerID;
	BOOL					m_bIsWasted;
	BYTE					m_byteSpectateID;
	BYTE					m_byteUpdateFromNetwork;
	BOOL					m_bIsActive;

	char _padB[287];

public:

	VECTOR					m_vecPos;

	char _pad136[36];

	BYTE					m_byteState;

	char _pad15B[44];

	BYTE GetState() { return m_byteState; };

	BOOL IsActive() { return m_bIsActive; };
	BOOL IsWasted() { return m_bIsWasted; };

	void Process();
	BOOL ValidateSyncData();
	void BroadcastSyncData();

	void Say(PCHAR szText, BYTE byteTextLength);
	void SetID(BYTE bytePlayerID) { m_bytePlayerID = bytePlayerID; };

	BYTE GetSpectate() { return m_byteSpectateID; };
};

#endif
