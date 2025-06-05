
#include "../main.h"

// TODO: These RPC functions
void ServerJoin(PCHAR Data, int iBitLength, PlayerID sender) {}
void GameSettings(PCHAR Data, int iBitLength, PlayerID sender) {}
void ServerQuit(PCHAR Data, int iBitLength, PlayerID sender) {}
void InitGame(PCHAR Data, int iBitLength, PlayerID sender) {}
void Chat(PCHAR Data, int iBitLength, PlayerID sender) {}
void RequestClass(PCHAR Data, int iBitLength, PlayerID sender) {}
void Spawn(PCHAR Data, int iBitLength, PlayerID sender) {}
void Death(PCHAR Data, int iBitLength, PlayerID sender) {}
void OwnDeath(PCHAR Data, int iBitLength, PlayerID sender) {}
void EnterVehicle(PCHAR Data, int iBitLength, PlayerID sender) {}
void ExitVehicle(PCHAR Data, int iBitLength, PlayerID sender) {}
void VehicleSpawn(PCHAR Data, int iBitLength, PlayerID sender) {}
void UpdateScPing(PCHAR Data, int iBitLength, PlayerID sender) {}
void ConnectionRejected(PCHAR Data, int iBitLength, PlayerID sender) {}
void Passenger(PCHAR Data, int iBitLength, PlayerID sender) {}
void IsAdmin(PCHAR Data, int iBitLength, PlayerID sender) {}
void NotAdmin(PCHAR Data, int iBitLength, PlayerID sender) {}
void AdminChat(PCHAR Data, int iBitLength, PlayerID sender) {}
void Set(PCHAR Data, int iBitLength, PlayerID sender) {}
void MsgChat(PCHAR Data, int iBitLength, PlayerID sender) {}
void ME(PCHAR Data, int iBitLength, PlayerID sender) {}
void TeamChat(PCHAR Data, int iBitLength, PlayerID sender) {}
void PickupSpawn(PCHAR Data, int iBitLength, PlayerID sender) {}
void PickedUp(PCHAR Data, int iBitLength, PlayerID sender) {}
void Kicked(PCHAR Data, int iBitLength, PlayerID sender) {}
void Banned(PCHAR Data, int iBitLength, PlayerID sender) {}
void DoAnim(PCHAR Data, int iBitLength, PlayerID sender) {}
void SpecOn(PCHAR Data, int iBitLength, PlayerID sender) {}
void SetHour(PCHAR Data, int iBitLength, PlayerID sender) {}
void SetMinute(PCHAR Data, int iBitLength, PlayerID sender) {}
void SetWeather(PCHAR Data, int iBitLength, PlayerID sender) {}
void RequestAmmu(PCHAR Data, int iBitLength, PlayerID sender) {}
void RequestWep(PCHAR Data, int iBitLength, PlayerID sender) {}
void PlayerDead(PCHAR Data, int iBitLength, PlayerID sender) {}
void PlayerFallen(PCHAR Data, int iBitLength, PlayerID sender) {}
void SendSpikeStrip(PCHAR Data, int iBitLength, PlayerID sender) {}
void SetWepDam(PCHAR Data, int iBitLength, PlayerID sender) {}
void SetSpike(PCHAR Data, int iBitLength, PlayerID sender) {}
void ClientMessage(PCHAR Data, int iBitLength, PlayerID sender) {}
void DeleteVehicle(PCHAR Data, int iBitLength, PlayerID sender) {}

//----------------------------------------------------

void RegisterRPCs(RakClientInterface * pRakClient)
{
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,ServerJoin);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,GameSettings);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,ServerQuit);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,InitGame);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,Chat);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,RequestClass);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,Spawn);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,Death);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,OwnDeath);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,EnterVehicle);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,ExitVehicle);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,VehicleSpawn);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,UpdateScPing);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,ConnectionRejected);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,Passenger);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,IsAdmin);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,NotAdmin);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,AdminChat);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,Set);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,MsgChat);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,ME);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,TeamChat);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,PickupSpawn);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,PickedUp);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,Kicked);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,Banned);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,DoAnim);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,SpecOn);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,SetHour);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,SetMinute);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,SetWeather);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,RequestAmmu);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,RequestWep);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,PlayerDead);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,PlayerFallen);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,SendSpikeStrip);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,SetWepDam);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,SetSpike);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,ClientMessage);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,DeleteVehicle);
}

//----------------------------------------------------

void UnRegisterRPCs(RakClientInterface * pRakClient)
{
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,ServerJoin);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,GameSettings);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,ServerQuit);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,InitGame);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,Chat);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,RequestClass);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,Spawn);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,Death);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,OwnDeath);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,EnterVehicle);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,ExitVehicle);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,VehicleSpawn);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,UpdateScPing);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,ConnectionRejected);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,Passenger);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,IsAdmin);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,NotAdmin);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,AdminChat);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,Set);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,MsgChat);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,ME);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,TeamChat);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,PickupSpawn);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,PickedUp);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,Kicked);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,Banned);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,DoAnim);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,SpecOn);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,SetHour);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,SetMinute);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,SetWeather);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,RequestAmmu);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,RequestWep);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,PlayerDead);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,PlayerFallen);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,SendSpikeStrip);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,SetWepDam);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,SetSpike);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,ClientMessage);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakClient,DeleteVehicle);
}

//----------------------------------------------------
