
#include "main.h"

RakServerInterface		*pRak=0;

//----------------------------------------------------

void ClientJoin(RPCParameters *rpcParams) {} // TODO: ClientJoin

void ClientJoinPatch(RPCParameters *rpcParams)
{
	RakNet::BitStream bsData(rpcParams->input,(rpcParams->numberOfBitsOfData-1)/8+1,false);
	RakNet::BitStream bsSend;

	BYTE bytePlayerID = pRak->GetIndexFromPlayerID(rpcParams->sender);

	int iVersion;
	bsData.Read(iVersion);

	pRcon->ConsolePrintf("[joinpatch] %u %i", bytePlayerID, iVersion);

	pNetGame->GetGameMode()->OnPlayerVersion(bytePlayerID, iVersion);
}

void Chat(RPCParameters *rpcParams) {} // TODO: Chat
void ME(RPCParameters *rpcParams) {} // TODO: ME
void MsgChat(RPCParameters *rpcParams) {} // TODO: MsgChat
void TeamChat(RPCParameters *rpcParams) {} // TODO: TeamChat
void RequestClass(RPCParameters *rpcParams) {} // TODO: RequestClass
void Spawn(RPCParameters *rpcParams) {} // TODO: Spawn
void Death(RPCParameters *rpcParams) {} // TODO: Death
void EnterVehicle(RPCParameters *rpcParams) {} // TODO: EnterVehicle
void ExitVehicle(RPCParameters *rpcParams) {} // TODO: ExitVehicle
void UpdateScoreAndPing(RPCParameters *rpcParams) {} // TODO: UpdateScoreAndPing
void Admin(RPCParameters *rpcParams) {} // TODO: Admin
void KickPlayer(RPCParameters *rpcParams) {} // TODO: KickPlayer
void BanIPAddress(RPCParameters *rpcParams) {} // TODO: BanIPAddress
void Ban(RPCParameters *rpcParams) {} // TODO: Ban
void Set(RPCParameters *rpcParams) {} // TODO: Set
void SetA(RPCParameters *rpcParams) {} // TODO: SetA
void Quit(RPCParameters *rpcParams) {} // TODO: Quit
void QuitA(RPCParameters *rpcParams) {} // TODO: QuitA
void PickedUp(RPCParameters *rpcParams) {} // TODO: PickedUp
void DoAnim(RPCParameters *rpcParams) {} // TODO: DoAnim
void Spec(RPCParameters *rpcParams) {} // TODO: Spec
void RequestAmmu(RPCParameters *rpcParams) {} // TODO: RequestAmmu
void RequestWep(RPCParameters *rpcParams) {} // TODO: RequestWep
void Commanda(RPCParameters *rpcParams) {} // TODO: Commanda
void SetMin(RPCParameters *rpcParams) {} // TODO: SetMin
void SetHr(RPCParameters *rpcParams) {} // TODO: SetHr
void SetWeather(RPCParameters *rpcParams) {} // TODO: SetWeather
void SetTimeRate(RPCParameters *rpcParams) {} // TODO: SetTimeRate
void PlayerDied(RPCParameters *rpcParams) {} // TODO: PlayerDied
void PlayerFell(RPCParameters *rpcParams) {} // TODO: PlayerFell
void CrashDump(RPCParameters *rpcParams) {} // TODO: CrashDump
void SendSpikeStrip(RPCParameters *rpcParams) {} // TODO: SendSpikeStrip

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
