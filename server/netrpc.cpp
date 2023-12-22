
#include "main.h"

RakServerInterface		*pRak=0;

void ClientJoin(RPCParameters *rpcParams) {} // TODO:
void ClientJoinPatch(RPCParameters *rpcParams) {} // TODO:
void Chat(RPCParameters *rpcParams) {} // TODO:
void ME(RPCParameters *rpcParams) {} // TODO:
void MsgChat(RPCParameters *rpcParams) {} // TODO:
void TeamChat(RPCParameters *rpcParams) {} // TODO:
void RequestClass(RPCParameters *rpcParams) {} // TODO:
void Spawn(RPCParameters *rpcParams) {} // TODO:
void Death(RPCParameters *rpcParams) {} // TODO:
void EnterVehicle(RPCParameters *rpcParams) {} // TODO:
void ExitVehicle(RPCParameters *rpcParams) {} // TODO:
void UpdateScoreAndPing(RPCParameters *rpcParams) {} // TODO:
void Admin(RPCParameters *rpcParams) {} // TODO:
void KickPlayer(RPCParameters *rpcParams) {} // TODO:
void BanIPAddress(RPCParameters *rpcParams) {} // TODO:
void Ban(RPCParameters *rpcParams) {} // TODO:
void Set(RPCParameters *rpcParams) {} // TODO:
void SetA(RPCParameters *rpcParams) {} // TODO:
void Quit(RPCParameters *rpcParams) {} // TODO:
void QuitA(RPCParameters *rpcParams) {} // TODO:
void PickedUp(RPCParameters *rpcParams) {} // TODO:
void DoAnim(RPCParameters *rpcParams) {} // TODO:
void Spec(RPCParameters *rpcParams) {} // TODO:
void RequestAmmu(RPCParameters *rpcParams) {} // TODO:
void RequestWep(RPCParameters *rpcParams) {} // TODO:
void Commanda(RPCParameters *rpcParams) {} // TODO:
void SetMin(RPCParameters *rpcParams) {} // TODO:
void SetHr(RPCParameters *rpcParams) {} // TODO:
void SetWeather(RPCParameters *rpcParams) {} // TODO:
void SetTimeRate(RPCParameters *rpcParams) {} // TODO:
void PlayerDied(RPCParameters *rpcParams) {} // TODO:
void PlayerFell(RPCParameters *rpcParams) {} // TODO:
void CrashDump(RPCParameters *rpcParams) {} // TODO:
void SendSpikeStrip(RPCParameters *rpcParams) {} // TODO:

//----------------------------------------------------

void RegisterRPCs(RakServerInterface * pRakServer)
{
	pRak = pRakServer;

	REGISTER_STATIC_RPC(pRakServer, ClientJoin);
	REGISTER_STATIC_RPC(pRakServer, ClientJoinPatch);
	REGISTER_STATIC_RPC(pRakServer, Chat);
	REGISTER_STATIC_RPC(pRakServer, ME);
	REGISTER_STATIC_RPC(pRakServer, MsgChat);
	REGISTER_STATIC_RPC(pRakServer, TeamChat);
	REGISTER_STATIC_RPC(pRakServer, RequestClass);
	REGISTER_STATIC_RPC(pRakServer, Spawn);
	REGISTER_STATIC_RPC(pRakServer, Death);
	REGISTER_STATIC_RPC(pRakServer, EnterVehicle);
	REGISTER_STATIC_RPC(pRakServer, ExitVehicle);
	REGISTER_STATIC_RPC(pRakServer, UpdateScoreAndPing);
	REGISTER_STATIC_RPC(pRakServer, Admin);
	REGISTER_STATIC_RPC(pRakServer, KickPlayer);
	REGISTER_STATIC_RPC(pRakServer, BanIPAddress);
	REGISTER_STATIC_RPC(pRakServer, Ban);
	REGISTER_STATIC_RPC(pRakServer, Set);
	REGISTER_STATIC_RPC(pRakServer, SetA);
	REGISTER_STATIC_RPC(pRakServer, Quit);
	REGISTER_STATIC_RPC(pRakServer, QuitA);
	REGISTER_STATIC_RPC(pRakServer, PickedUp);
	REGISTER_STATIC_RPC(pRakServer, DoAnim);
	REGISTER_STATIC_RPC(pRakServer, Spec);
	REGISTER_STATIC_RPC(pRakServer, RequestAmmu);
	REGISTER_STATIC_RPC(pRakServer, RequestWep);
	REGISTER_STATIC_RPC(pRakServer, Commanda);
	REGISTER_STATIC_RPC(pRakServer, SetMin);
	REGISTER_STATIC_RPC(pRakServer, SetHr);
	REGISTER_STATIC_RPC(pRakServer, SetWeather);
	REGISTER_STATIC_RPC(pRakServer, SetTimeRate);
	REGISTER_STATIC_RPC(pRakServer, PlayerDied);
	REGISTER_STATIC_RPC(pRakServer, PlayerFell);
	REGISTER_STATIC_RPC(pRakServer, CrashDump);
	REGISTER_STATIC_RPC(pRakServer, SendSpikeStrip);
}

//----------------------------------------------------

void UnRegisterRPCs(RakServerInterface * pRakServer)
{
	UNREGISTER_STATIC_RPC(pRakServer, ClientJoin);
	UNREGISTER_STATIC_RPC(pRakServer, ClientJoinPatch);
	UNREGISTER_STATIC_RPC(pRakServer, Chat);
	UNREGISTER_STATIC_RPC(pRakServer, ME);
	UNREGISTER_STATIC_RPC(pRakServer, MsgChat);
	UNREGISTER_STATIC_RPC(pRakServer, TeamChat);
	UNREGISTER_STATIC_RPC(pRakServer, RequestClass);
	UNREGISTER_STATIC_RPC(pRakServer, Spawn);
	UNREGISTER_STATIC_RPC(pRakServer, Death);
	UNREGISTER_STATIC_RPC(pRakServer, EnterVehicle);
	UNREGISTER_STATIC_RPC(pRakServer, ExitVehicle);
	UNREGISTER_STATIC_RPC(pRakServer, UpdateScoreAndPing);
	UNREGISTER_STATIC_RPC(pRakServer, Admin);
	UNREGISTER_STATIC_RPC(pRakServer, KickPlayer);
	UNREGISTER_STATIC_RPC(pRakServer, BanIPAddress);
	UNREGISTER_STATIC_RPC(pRakServer, Ban);
	UNREGISTER_STATIC_RPC(pRakServer, Set);
	UNREGISTER_STATIC_RPC(pRakServer, SetA);
	UNREGISTER_STATIC_RPC(pRakServer, Quit);
	UNREGISTER_STATIC_RPC(pRakServer, QuitA);
	UNREGISTER_STATIC_RPC(pRakServer, PickedUp);
	UNREGISTER_STATIC_RPC(pRakServer, DoAnim);
	UNREGISTER_STATIC_RPC(pRakServer, Spec);
	UNREGISTER_STATIC_RPC(pRakServer, RequestAmmu);
	UNREGISTER_STATIC_RPC(pRakServer, RequestWep);
	UNREGISTER_STATIC_RPC(pRakServer, Commanda);
	UNREGISTER_STATIC_RPC(pRakServer, SetMin);
	UNREGISTER_STATIC_RPC(pRakServer, SetHr);
	UNREGISTER_STATIC_RPC(pRakServer, SetWeather);
	UNREGISTER_STATIC_RPC(pRakServer, SetTimeRate);
	UNREGISTER_STATIC_RPC(pRakServer, PlayerDied);
	UNREGISTER_STATIC_RPC(pRakServer, PlayerFell);
	UNREGISTER_STATIC_RPC(pRakServer, CrashDump);
	UNREGISTER_STATIC_RPC(pRakServer, SendSpikeStrip);

	pRak = 0;
}

//----------------------------------------------------
