
#include "netgame.h"

RakServerInterface		*pRak=0;

void ClientJoin(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: ClientJoin
void Chat(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: Chat
void ME(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: ME
void MsgChat(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: MsgChat
void TeamChat(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: TeamChat
void RequestClass(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: RequestClass
void Spawn(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: Spawn
void Death(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: Death
void EnterVehicle(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: EnterVehicle
void ExitVehicle(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: ExitVehicle
void UpdateScoreAndPing(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: UpdateScoreAndPing
void Admin(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: Admin
void KickPlayer(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: KickPlayer
void BanIPAddress(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: BanIPAddress
void Ban(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: Ban
void Set(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: Set
void SetA(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: SetA
void Quit(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: Quit
void PickedUp(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: PickedUp
void DoAnim(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: DoAnim
void Spec(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: Spec
void RequestAmmu(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: RequestAmmu
void RequestWep(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: RequestWep
void Commanda(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: Commanda
void SetMin(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: SetMin
void SetHr(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: SetHr
void SetWeather(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: SetWeather
void SetTimeRate(PCHAR Data, int iBitLength, PlayerID sender) {} // TODO: SetTimeRate

//----------------------------------------------------

void RegisterRPCs(RakServerInterface * pRakServer)
{
	pRak = pRakServer;

	REGISTER_AS_REMOTE_PROCEDURE_CALL(pRakServer, ClientJoin);
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
}

//----------------------------------------------------
