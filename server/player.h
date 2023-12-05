
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
	BYTE					field_5;
	BYTE					m_byteUpdateFromNetwork;
	BOOL					m_bIsActive;

public:

	VECTOR					m_vecPos;

	BYTE					m_byteState;

	BYTE GetState() { return m_byteState; };

	BOOL IsActive() { return m_bIsActive; };
	BOOL IsWasted() { return m_bIsWasted; };

	void Process();
	BOOL ValidateSyncData();
	void BroadcastSyncData();

	void SetID(BYTE bytePlayerID) { m_bytePlayerID = bytePlayerID; };
};

#endif
