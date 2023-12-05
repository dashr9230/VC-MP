
#include "main.h"

#define CHECK_PARAMS(n) { if (params[0] != (n * sizeof(cell))) { logprintf("SCRIPT: Bad parameter count (%d != %d): ", params[0], n); return 0; } }

char* format_amxstring(AMX *amx, cell *params, int parm, int &len);
int set_amxstring(AMX *amx,cell amx_addr,const char *source,int max);

extern BOOL bGameModeFinished;
extern CNetGame* pNetGame;

//----------------------------------------------------------------------------------

static cell AMX_NATIVE_CALL n_GameModeExit(AMX *amx, cell *params)
{
	if(pNetGame->SetNextScriptFile(NULL)) {
		bGameModeFinished = TRUE;
	} else {
		logprintf("The gamemode finished and I couldn't start another script.");
		fcloseall();
		exit(1);
	}
	return 0;
}

//----------------------------------------------------------------------------------

static cell AMX_NATIVE_CALL n_SetGameModeText(AMX *amx, cell *params)
{
	CHECK_PARAMS(1);

	char* szGameModeText;
	amx_StrParam(amx, params[1], szGameModeText);
	pConsole->SetStringVariable("gamemodetext", szGameModeText);

	return 0;
}

//----------------------------------------------------------------------------------

static cell AMX_NATIVE_CALL n_SetTeamCount(AMX *amx, cell *params)
{
	return 0;
}

//----------------------------------------------------------------------------------

static cell AMX_NATIVE_CALL n_AddPlayerClass(AMX *amx, cell *params)
{
	PLAYER_SPAWN_INFO Spawn;

	Spawn.byteTeam = 255; // Auto team assignment for the old AddPlayerClass
	Spawn.byteSkin = (BYTE)params[1];
	Spawn.vecPos.X = amx_ctof(params[2]);
	Spawn.vecPos.Y = amx_ctof(params[3]);
	Spawn.vecPos.Z = amx_ctof(params[4]);
	Spawn.fRotation = amx_ctof(params[5]);

	// WEAPONS
	Spawn.iSpawnWeapons[0] = (int)params[6];
	Spawn.iSpawnWeaponsAmmo[0] = (int)params[7];
	Spawn.iSpawnWeapons[1] = (int)params[8];
	Spawn.iSpawnWeaponsAmmo[1] = (int)params[9];
	Spawn.iSpawnWeapons[2] = (int)params[10];
	Spawn.iSpawnWeaponsAmmo[2] = (int)params[11];

	pNetGame->AddSpawn(&Spawn);
	return 0;
}

//----------------------------------------------------------------------------------

static cell AMX_NATIVE_CALL n_AddPlayerClassEx(AMX *amx, cell *params)
{
	PLAYER_SPAWN_INFO Spawn;

	// BASE INFO
	Spawn.byteTeam = (BYTE)params[1];
	Spawn.byteSkin = (BYTE)params[2];
	Spawn.vecPos.X = amx_ctof(params[3]);
	Spawn.vecPos.Y = amx_ctof(params[4]);
	Spawn.vecPos.Z = amx_ctof(params[5]);
	Spawn.fRotation = amx_ctof(params[6]);

	// WEAPONS
	Spawn.iSpawnWeapons[0] = (int)params[7];
	Spawn.iSpawnWeaponsAmmo[0] = (int)params[8];
	Spawn.iSpawnWeapons[1] = (int)params[9];
	Spawn.iSpawnWeaponsAmmo[1] = (int)params[10];
	Spawn.iSpawnWeapons[2] = (int)params[11];
	Spawn.iSpawnWeaponsAmmo[2] = (int)params[12];

	pNetGame->AddSpawn(&Spawn);
	return 0;
}

//----------------------------------------------------------------------------------

static cell AMX_NATIVE_CALL n_AddStaticVehicle(AMX *amx, cell *params)
{
	CHECK_PARAMS(7);

	VECTOR vecPos;
	vecPos.X = amx_ctof(params[2]);
	vecPos.Y = amx_ctof(params[3]);
	vecPos.Z = amx_ctof(params[4]);

	BYTE ret = pNetGame->GetVehiclePool()->New((BYTE)params[1], &vecPos, amx_ctof(params[5]),
		(int)params[6], (int)params[7]);

	return ret;
}

//----------------------------------------------------------------------------------

static cell AMX_NATIVE_CALL n_AddStaticVehicleEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(7);

	VECTOR vecPos;
	vecPos.X = amx_ctof(params[2]);
	vecPos.Y = amx_ctof(params[3]);
	vecPos.Z = amx_ctof(params[4]);

	BYTE ret = pNetGame->GetVehiclePool()->New((BYTE)params[1], &vecPos, amx_ctof(params[5]),
		(int)params[6], (int)params[7]);

	return ret;
}

//----------------------------------------------------------------------------------

// native AddStaticPickup(id,type,Float:X,Float:Y,Float:Z,amount);
static cell AMX_NATIVE_CALL n_AddStaticPickup(AMX *amx, cell *params)
{
	VECTOR vecPos;
	vecPos.X = amx_ctof(params[3]);
	vecPos.Y = amx_ctof(params[4]);
	vecPos.Z = amx_ctof(params[5]);

	pNetGame->GetPickupPool()->New((int)params[1], (int)params[2], &vecPos, (int)params[6]);
	return 1;
}

//----------------------------------------------------------------------------------














//----------------------------------------------------------------------------------

// native print(const string[])
static cell AMX_NATIVE_CALL n_print(AMX* amx, cell* params)
{
	CHECK_PARAMS(1);

	char* msg;
	amx_StrParam(amx, params[1], msg);
	logprintf("%s",msg);
	return 0;
}

//----------------------------------------------------------------------------------

// native printf(const format[], {Float,_}:...)
static cell AMX_NATIVE_CALL n_printf(AMX *amx, cell *params)
{
	int len;
	logprintf("%s",format_amxstring(amx, params, 1, len));

	return 0;
}

//----------------------------------------------------------------------------------

// native format(output[], len, const format[], {Float,_}:...)
static cell AMX_NATIVE_CALL n_format(AMX *amx, cell *params)
{
  int len;
  return set_amxstring(amx, params[1], format_amxstring(amx, params, 3, len), params[2]);
}

//----------------------------------------------------------------------------------

// native SetTimer(funcname[], interval, repeating)
static cell AMX_NATIVE_CALL n_SetTimer(AMX *amx, cell *params)
{
	CHECK_PARAMS(3);

	char* szFuncName;
	amx_StrParam(amx, params[1], szFuncName);
	return pNetGame->GetGameMode()->GetTimers()->New(szFuncName, params[2], params[3], amx);
}

//----------------------------------------------------------------------------------

// native KillTimer(timerid)
static cell AMX_NATIVE_CALL n_KillTimer(AMX *amx, cell *params)
{
	CHECK_PARAMS(1);

	pNetGame->GetGameMode()->GetTimers()->Delete(params[1]);

	return 1;
}

//----------------------------------------------------------------------------------

// native GetTickCount()
static cell AMX_NATIVE_CALL n_GetTickCount(AMX *amx, cell *params)
{
	CHECK_PARAMS(0);

#ifdef WIN32
	return (cell)GetTickCount();
#else
	return 0;
#endif
}

//----------------------------------------------------------------------------------
// native GetMaxPlayers()
static cell AMX_NATIVE_CALL n_GetMaxPlayers(AMX *amx, cell *params)
{
	CHECK_PARAMS(0);
	
	extern CConsole *pConsole;
	return pConsole->GetIntVariable("maxplayers");
}




//----------------------------------------------------------------------------------

AMX_NATIVE_INFO custom_Natives[] =
{
	// Util
	{ "print",					n_print },
	{ "printf",					n_printf },
	{ "format",					n_format },
	{ "SetTimer",				n_SetTimer },
	{ "KillTimer",				n_KillTimer },
	{ "GetTickCount",			n_GetTickCount },
	{ "GetMaxPlayers",			n_GetMaxPlayers },

	// Game
	{ "GameModeExit",			n_GameModeExit },
	{ "SetGameModeText",		n_SetGameModeText },
	{ "SetTeamCount",			n_SetTeamCount },
	{ "AddPlayerClass",			n_AddPlayerClass },
	{ "AddPlayerClassEx",		n_AddPlayerClassEx },
	{ "AddStaticVehicle",		n_AddStaticVehicle },
	{ "AddStaticVehicleEx",		n_AddStaticVehicleEx },
	{ "AddStaticPickup", n_AddStaticPickup },
/*	{ "SetWorldBounds", n_SetWorldBounds },
	{ "ShowNameTags", n_ShowNameTags },
	{ "ShowPlayerMarkers", n_ShowPlayerMarkers },
	{ "SetWorldTime", n_SetWorldTime },
	{ "GetWeaponName", n_GetWeaponName },
	{ "SetGravity", n_SetGravity },
	{ "ResetNormalGravity", n_ResetNormalGravity },
	{ "SetGamespeed", n_SetGamespeed },
	{ "ResetNormalGamespeed", n_ResetNormalGamespeed },
	{ "SetGravityForPlayer", n_SetGravityForPlayer },
	{ "ResetNormalGravityForPlayer", n_ResetNormalGravityForPlayer },
	{ "SetGamespeedForPlayer", n_SetGamespeedForPlayer },
	{ "ResetNormalGamespeedForPlayer", n_ResetNormalGamespeedForPlayer },
	{ "ToggleWhiteScanlinesForAll", n_ToggleWhiteScanlinesForAll },
	{ "ToggleWhiteScanlinesForPlayer", n_ToggleWhiteScanlinesForPlayer },
	{ "ToggleGreenScanlinesForAll", n_ToggleGreenScanlinesForAll },
	{ "ToggleGreenScanlinesForPlayer", n_ToggleGreenScanlinesForPlayer },
	{ "ToggleWidescreenForAll", n_ToggleWidescreenForAll },
	{ "ToggleWidescreenForPlayer", n_ToggleWidescreenForPlayer },
	{ "Flyingcars", n_Flyingcars },
	{ "Taxiboostjump", n_Taxiboostjump },
	{ "FastSwitch", n_FastSwitch },
	{ "Jumpswitch", n_Jumpswitch },
	{ "SetWeaponDamage", n_SetWeaponDamage },
	{ "SetSpikes", n_SetSpikes },
	{ "DisableDriveby", n_DisableDriveby },
	{ "PerfectHandling", n_PerfectHandling },
	{ "Syncframelimiter", n_Syncframelimiter },
	{ "RemovePlayerMarker", n_RemovePlayerMarker },
	{ "SetPlayerMarker", n_SetPlayerMarker },
	{ "SetWantedLevel", n_SetWantedLevel },
	{ "SetWaterLevel", n_SetWaterLevel },
	{ "IsPlayerAdmin", n_IsPlayerAdmin },
	{ "Kick", n_Kick },
	{ "Ban", n_Ban },
	{ "SetPlayerTeam", n_SetPlayerTeam },
	{ "SetPlayerFriendlyFire", n_SetPlayerFriendlyFire },
	{ "GetPlayerTeam", n_GetPlayerTeam },
	{ "SetPlayerSkin", n_SetPlayerSkin },
	{ "GetPlayerPos", n_GetPlayerPos },
	{ "SetPlayerPos", n_SetPlayerPos },
	{ "SetPlayerStartPos", n_SetPlayerStartPos },
	{ "GetPlayerHealth", n_GetPlayerHealth },
	{ "SetPlayerHealth", n_SetPlayerHealth },
	{ "GetPlayerArmour", n_GetPlayerArmour },
	{ "SetPlayerArmour", n_SetPlayerArmour },
	{ "SetPlayerWeapon", n_SetPlayerWeapon },
	{ "GetPlayerVehicleID", n_GetPlayerVehicleID },
	{ "PutPlayerInVehicle", n_PutPlayerInVehicle },
	{ "RemovePlayerFromVehicle", n_RemovePlayerFromVehicle },
	{ "IsPlayerInVehicle", n_IsPlayerInVehicle },
	{ "IsPlayerInAnyVehicle", n_IsPlayerInAnyVehicle },
	{ "IsPlayerDriver_Passanger", n_IsPlayerDriver_Passanger },
	{ "GetPlayerName", n_GetPlayerName },
	{ "GetPlayerVehicleID", n_GetPlayerVehicleID },
	{ "SetCameraLookAt", n_SetCameraLookAt },
	{ "SetCameraPos", n_SetCameraPos },
	{ "TogglePlayerControllable", n_TogglePlayerControllable },
	{ "SetPlayerAnimation", n_SetPlayerAnimation },
	{ "SetPlayerDrunk", n_SetPlayerDrunk },
	{ "PlayerPlaySound", n_PlayerPlaySound },
	{ "SetPlayerScore", n_SetPlayerScore },
	{ "GetPlayerScore", n_GetPlayerScore },
	{ "SetPlayerFacingAngle", n_SetPlayerFacingAngle },
	{ "GetPlayerFacingAngle", n_GetPlayerFacingAngle },
	{ "GivePlayerMoney", n_GivePlayerMoney },
	{ "SetPlayerMoney", n_SetPlayerMoney },
	{ "GetPlayerMoney", n_GetPlayerMoney },
	{ "ResetPlayerMoney", n_ResetPlayerMoney },
	{ "IsPlayerConnected", n_IsPlayerConnected },
	{ "GetPlayerState", n_GetPlayerState },
	{ "ResetPlayerWeapons", n_ResetPlayerWeapons },
	{ "GivePlayerWeapon", n_GivePlayerWeapon },
	{ "GetPlayerIp", n_GetPlayerIp },
	{ "GetPlayerPing", n_GetPlayerPing },
	{ "GetPlayerIDFromName", n_GetPlayerIDFromName },
	{ "SetPlayerDriveOnWater", n_SetPlayerDriveOnWater },
	{ "EnableStuntBike", n_EnableStuntBike },
	{ "EnableShootInAir", n_EnableShootInAir },
	{ "GetVehiclePos", n_GetVehiclePos },
	{ "SetVehiclePos", n_SetVehiclePos },
	{ "SetVehicleHealth", n_SetVehicleHealth },
	{ "GetVehicleHealth", n_GetVehicleHealth },
	{ "SetVehicleToRespawn", n_SetVehicleToRespawn },
	{ "SetVehicleDoorsStatus", n_SetVehicleDoorsStatus },
	{ "SetVehicleTyre", n_SetVehicleTyre },
	{ "KillVehicleEngine", n_KillVehicleEngine },
	{ "PutDirectlyInVehicle", n_PutDirectlyInVehicle },
	{ "SetVehicleAlarm", n_SetVehicleAlarm },
	{ "SetVehicleLights", n_SetVehicleLights },
	{ "CreateVehicle", n_CreateVehicle },
	{ "DeleteVehicle", n_DeleteVehicle },
	{ "ChangeVehicleColor", n_ChangeVehicleColor },
	{ "SendClientMessage", n_SendClientMessage },
	{ "SendClientMessageToAll", n_SendClientMessageToAll },
	{ "SendDeathMessage", n_SendDeathMessage },
	{ "SetDeathMessage", n_SetDeathMessage },
	{ "GameTextForAll", n_GameTextForAll },
	{ "GameTextForPlayer", n_GameTextForPlayer },
	{ "GameTextForAllBottom", n_GameTextForAllBottom },
	{ "GameTextForPlayerBottom", n_GameTextForPlayerBottom },
	{ "SendRconEvent", n_SendRconEvent },
	{ "SendRconCommand", n_SendRconCommand },
*/
	{ NULL, NULL }
};

//----------------------------------------------------------------------------------

int amx_CustomInit(AMX *amx)
{
  return amx_Register(amx, custom_Natives, -1);
}

//----------------------------------------------------------------------------------
