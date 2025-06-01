
#pragma once

#define UPDATE_TYPE_NONE		0
#define UPDATE_TYPE_FULL_ONFOOT	1
#define UPDATE_TYPE_FULL_INCAR	3
#define UPDATE_TYPE_SPECTATE	6

#define PLAYER_STATE_NONE						0
#define PLAYER_STATE_ONFOOT						1

#define PLAYER_STATE_SPECTATING					9

typedef struct _ONFOOT_SYNC_DATA
{
	BYTE _gap0[39];

} ONFOOT_SYNC_DATA;

typedef struct _AIM_SYNC_DATA
{
	BYTE _gap0[28];

} AIM_SYNC_DATA;

typedef struct _INCAR_SYNC_DATA
{
	BYTE _gap0[56];

} INCAR_SYNC_DATA;

typedef struct _PLAYER_SPAWN_INFO
{
	BYTE byteTeam;
	BYTE byteSkin;
	VECTOR vecPos;
	float fRotation;
	int iSpawnWeapons[3];
	int iSpawnWeaponsAmmo[3];
} PLAYER_SPAWN_INFO;

//----------------------------------------------------

class CPlayer
{
private:
	BYTE					m_bytePlayerID;
	BOOL					m_bIsActive;
	BOOL					m_bIsWasted;
	BYTE					m_byteSpectateID;
	BYTE					m_byteUpdateFromNetwork;
	PLAYER_SPAWN_INFO		m_SpawnInfo;
	ONFOOT_SYNC_DATA		m_ofSync;
	AIM_SYNC_DATA			m_aimSync;
	INCAR_SYNC_DATA			m_icSync;

public:

	VECTOR					m_vecPos;

	float					m_fVehicleHealth;
	BYTE					m_byteHealth;
	BYTE					m_byteArmour;
	BYTE					m_byteCurrentWeapon;

	BYTE					m_byteState;
	int						m_iMoney;

	BYTE					m_byteVehicleID;

	CPlayer();
	~CPlayer() {};

	BOOL IsActive() { return m_bIsActive; };
	BOOL IsWasted() { return m_bIsWasted; };

	void Process();
	BOOL ValidateSyncData();
	void BroadcastSyncData();

	void SetID(BYTE bytePlayerID) { m_bytePlayerID = bytePlayerID; };

	PLAYER_SPAWN_INFO * GetSpawnInfo() { return &m_SpawnInfo; };

	void UpdatePosition(float x, float y, float z) {
		m_vecPos.X=x;
		m_vecPos.Y=y;
		m_vecPos.Z=z;
	};

	void SetSpectate(BYTE byteSpectateID) { m_byteSpectateID = byteSpectateID; };
	BYTE GetSpectate() { return m_byteSpectateID; };

	BYTE GetState() { return m_byteState; };
	void SetState(BYTE byteState) {
		if(m_byteState != byteState)
			m_byteState = byteState;
	}

	BYTE GetCurrentCarID() { return m_byteVehicleID; };
	float GetCurrentCarHp() { return m_fVehicleHealth; };
	int GetMoney() { return m_iMoney; };
	BYTE GetHealth() { return m_byteHealth; };
	BYTE GetArmour() { return m_byteArmour; };
	BYTE GetCurrentWeapon() { return m_byteCurrentWeapon; };
};

//----------------------------------------------------
