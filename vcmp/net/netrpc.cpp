
#include "../main.h"

void ServerJoin(RPCParameters *rpcParams) {} // TODO
void GameSettings(RPCParameters *rpcParams) {} // TODO
void ServerQuit(RPCParameters *rpcParams) {} // TODO
void InitGame(RPCParameters *rpcParams) {} // TODO
void Chat(RPCParameters *rpcParams) {} // TODO
void RequestClass(RPCParameters *rpcParams) {} // TODO
void Spawn(RPCParameters *rpcParams) {} // TODO
void Death(RPCParameters *rpcParams) {} // TODO
void OwnDeath(RPCParameters *rpcParams) {} // TODO
void EnterVehicle(RPCParameters *rpcParams) {} // TODO
void ExitVehicle(RPCParameters *rpcParams) {} // TODO
void VehicleSpawn(RPCParameters *rpcParams) {} // TODO
void UpdateScPing(RPCParameters *rpcParams) {} // TODO
void ConnectionRejected(RPCParameters *rpcParams) {} // TODO
void Passenger(RPCParameters *rpcParams) {} // TODO
void IsAdmin(RPCParameters *rpcParams) {} // TODO
void NotAdmin(RPCParameters *rpcParams) {} // TODO
void AdminChat(RPCParameters *rpcParams) {} // TODO
void Set(RPCParameters *rpcParams) {} // TODO
void MsgChat(RPCParameters *rpcParams) {} // TODO
void ME(RPCParameters *rpcParams) {} // TODO
void TeamChat(RPCParameters *rpcParams) {} // TODO
void PickupSpawn(RPCParameters *rpcParams) {} // TODO
void PickedUp(RPCParameters *rpcParams) {} // TODO
void Kicked(RPCParameters *rpcParams) {} // TODO
void Banned(RPCParameters *rpcParams) {} // TODO
void DoAnim(RPCParameters *rpcParams) {} // TODO
void SpecOn(RPCParameters *rpcParams) {} // TODO
void SetHour(RPCParameters *rpcParams) {} // TODO
void SetMinute(RPCParameters *rpcParams) {} // TODO
void SetWeather(RPCParameters *rpcParams) {} // TODO
void RequestAmmu(RPCParameters *rpcParams) {} // TODO
void RequestWep(RPCParameters *rpcParams) {} // TODO
void PlayerDead(RPCParameters *rpcParams) {} // TODO
void PlayerFallen(RPCParameters *rpcParams) {} // TODO
void SendSpikeStrip(RPCParameters *rpcParams) {} // TODO
void SetWepDam(RPCParameters *rpcParams) {} // TODO
void SetSpike(RPCParameters *rpcParams) {} // TODO
void ClientMessage(RPCParameters *rpcParams) {} // TODO
void DeleteVehicle(RPCParameters *rpcParams) {} // TODO

//----------------------------------------------------

void RegisterRPCs(RakClientInterface * pRakClient)
{
	REGISTER_STATIC_RPC(pRakClient, ServerJoin);
	REGISTER_STATIC_RPC(pRakClient, GameSettings);
	REGISTER_STATIC_RPC(pRakClient, ServerQuit);
	REGISTER_STATIC_RPC(pRakClient, InitGame);
	REGISTER_STATIC_RPC(pRakClient, Chat);
	REGISTER_STATIC_RPC(pRakClient, RequestClass);
	REGISTER_STATIC_RPC(pRakClient, Spawn);
	REGISTER_STATIC_RPC(pRakClient, Death);
	REGISTER_STATIC_RPC(pRakClient, OwnDeath);
	REGISTER_STATIC_RPC(pRakClient, EnterVehicle);
	REGISTER_STATIC_RPC(pRakClient, ExitVehicle);
	REGISTER_STATIC_RPC(pRakClient, VehicleSpawn);
	REGISTER_STATIC_RPC(pRakClient, UpdateScPing);
	REGISTER_STATIC_RPC(pRakClient, ConnectionRejected);
	REGISTER_STATIC_RPC(pRakClient, Passenger);
	REGISTER_STATIC_RPC(pRakClient, IsAdmin);
	REGISTER_STATIC_RPC(pRakClient, NotAdmin);
	REGISTER_STATIC_RPC(pRakClient, AdminChat);
	REGISTER_STATIC_RPC(pRakClient, Set);
	REGISTER_STATIC_RPC(pRakClient, MsgChat);
	REGISTER_STATIC_RPC(pRakClient, ME);
	REGISTER_STATIC_RPC(pRakClient, TeamChat);
	REGISTER_STATIC_RPC(pRakClient, PickupSpawn);
	REGISTER_STATIC_RPC(pRakClient, PickedUp);
	REGISTER_STATIC_RPC(pRakClient, Kicked);
	REGISTER_STATIC_RPC(pRakClient, Banned);
	REGISTER_STATIC_RPC(pRakClient, DoAnim);
	REGISTER_STATIC_RPC(pRakClient, SpecOn);
	REGISTER_STATIC_RPC(pRakClient, SetHour);
	REGISTER_STATIC_RPC(pRakClient, SetMinute);
	REGISTER_STATIC_RPC(pRakClient, SetWeather);
	REGISTER_STATIC_RPC(pRakClient, RequestAmmu);
	REGISTER_STATIC_RPC(pRakClient, RequestWep);
	REGISTER_STATIC_RPC(pRakClient, PlayerDead);
	REGISTER_STATIC_RPC(pRakClient, PlayerFallen);
	REGISTER_STATIC_RPC(pRakClient, SendSpikeStrip);
	REGISTER_STATIC_RPC(pRakClient, SetWepDam);
	REGISTER_STATIC_RPC(pRakClient, SetSpike);
	REGISTER_STATIC_RPC(pRakClient, ClientMessage);
	REGISTER_STATIC_RPC(pRakClient, DeleteVehicle);
}

//----------------------------------------------------

void UnRegisterRPCs(RakClientInterface * pRakClient)
{
	UNREGISTER_STATIC_RPC(pRakClient, ServerJoin);
	UNREGISTER_STATIC_RPC(pRakClient, GameSettings);
	UNREGISTER_STATIC_RPC(pRakClient, ServerQuit);
	UNREGISTER_STATIC_RPC(pRakClient, InitGame);
	UNREGISTER_STATIC_RPC(pRakClient, Chat);
	UNREGISTER_STATIC_RPC(pRakClient, RequestClass);
	UNREGISTER_STATIC_RPC(pRakClient, Spawn);
	UNREGISTER_STATIC_RPC(pRakClient, Death);
	UNREGISTER_STATIC_RPC(pRakClient, OwnDeath);
	UNREGISTER_STATIC_RPC(pRakClient, EnterVehicle);
	UNREGISTER_STATIC_RPC(pRakClient, ExitVehicle);
	UNREGISTER_STATIC_RPC(pRakClient, VehicleSpawn);
	UNREGISTER_STATIC_RPC(pRakClient, UpdateScPing);
	UNREGISTER_STATIC_RPC(pRakClient, ConnectionRejected);
	UNREGISTER_STATIC_RPC(pRakClient, Passenger);
	UNREGISTER_STATIC_RPC(pRakClient, IsAdmin);
	UNREGISTER_STATIC_RPC(pRakClient, NotAdmin);
	UNREGISTER_STATIC_RPC(pRakClient, AdminChat);
	UNREGISTER_STATIC_RPC(pRakClient, Set);
	UNREGISTER_STATIC_RPC(pRakClient, MsgChat);
	UNREGISTER_STATIC_RPC(pRakClient, ME);
	UNREGISTER_STATIC_RPC(pRakClient, TeamChat);
	UNREGISTER_STATIC_RPC(pRakClient, PickupSpawn);
	UNREGISTER_STATIC_RPC(pRakClient, PickedUp);
	UNREGISTER_STATIC_RPC(pRakClient, Kicked);
	UNREGISTER_STATIC_RPC(pRakClient, Banned);
	UNREGISTER_STATIC_RPC(pRakClient, DoAnim);
	UNREGISTER_STATIC_RPC(pRakClient, SpecOn);
	UNREGISTER_STATIC_RPC(pRakClient, SetHour);
	UNREGISTER_STATIC_RPC(pRakClient, SetMinute);
	UNREGISTER_STATIC_RPC(pRakClient, SetWeather);
	UNREGISTER_STATIC_RPC(pRakClient, RequestAmmu);
	UNREGISTER_STATIC_RPC(pRakClient, RequestWep);
	UNREGISTER_STATIC_RPC(pRakClient, PlayerDead);
	UNREGISTER_STATIC_RPC(pRakClient, PlayerFallen);
	UNREGISTER_STATIC_RPC(pRakClient, SendSpikeStrip);
	UNREGISTER_STATIC_RPC(pRakClient, SetWepDam);
	UNREGISTER_STATIC_RPC(pRakClient, SetSpike);
	UNREGISTER_STATIC_RPC(pRakClient, ClientMessage);
	UNREGISTER_STATIC_RPC(pRakClient, DeleteVehicle);
}

//----------------------------------------------------
