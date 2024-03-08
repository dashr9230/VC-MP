
#pragma once

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
	int field_1;
	int field_5;
	char field_9;
	char field_A;
	PLAYER_SPAWN_INFO		m_SpawnInfo;
	char _gap35[141];
	BOOL					m_bHasSpawnInfo;
	char _gapC6[192];
	char field_186;
public:

	CPlayer();

	void SetID(BYTE bytePlayerID) { m_bytePlayerID = bytePlayerID; };

	void SetSpawnInfo(BYTE byteTeam, BYTE byteSkin, VECTOR * vecPos, float fRotation,
		int iSpawnWeapon1, int iSpawnWeapon1Ammo, int iSpawnWeapon2, int iSpawnWeapon2Ammo,
		int iSpawnWeapon3, int iSpawnWeapon3Ammo);

};

//----------------------------------------------------
