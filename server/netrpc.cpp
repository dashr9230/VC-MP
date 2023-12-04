
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

	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, ClientJoin);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, ClientJoinPatch);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, Chat);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, ME);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, MsgChat);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, TeamChat);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, RequestClass);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, Spawn);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, Death);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, EnterVehicle);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, ExitVehicle);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, UpdateScoreAndPing);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, Admin);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, KickPlayer);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, BanIPAddress);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, Ban);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, Set);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, SetA);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, Quit);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, QuitA);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, PickedUp);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, DoAnim);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, Spec);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, RequestAmmu);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, RequestWep);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, Commanda);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, SetMin);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, SetHr);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, SetWeather);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, SetTimeRate);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, PlayerDied);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, PlayerFell);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, CrashDump);
	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, SendSpikeStrip);
}

//----------------------------------------------------

void UnRegisterRPCs(RakServerInterface * pRakServer)
{
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, ClientJoin);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, ClientJoinPatch);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, Chat);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, ME);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, MsgChat);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, TeamChat);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, RequestClass);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, Spawn);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, Death);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, EnterVehicle);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, ExitVehicle);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, UpdateScoreAndPing);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, Admin);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, KickPlayer);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, BanIPAddress);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, Ban);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, Set);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, SetA);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, Quit);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, QuitA);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, PickedUp);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, DoAnim);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, Spec);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, RequestAmmu);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, RequestWep);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, Commanda);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, SetMin);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, SetHr);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, SetWeather);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, SetTimeRate);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, PlayerDied);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, PlayerFell);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, CrashDump);
	UNREGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, SendSpikeStrip);

	pRak = 0;
}

//----------------------------------------------------
