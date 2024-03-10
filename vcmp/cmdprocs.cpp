
#include "main.h"

extern CCmdWindow	 *pCmdWindow;

//----------------------------------------------------

void cmdDefaultCmdProc(PCHAR szCmd) {} // TODO: cmdDefaultCmdProc
void cmdQuit(PCHAR szCmd) {} // TODO: cmdQuit
void cmdAdmin(PCHAR szCmd) {} // TODO: cmdAdmin
void cmdKickEm(PCHAR szCmd) {} // TODO: cmdKickEm
void cmdGetIP(PCHAR szCmd) {} // TODO: cmdGetIP
void cmdBanIP(PCHAR szCmd) {} // TODO: cmdBanIP
void cmdBanTheirSorryAsses(PCHAR szCmd) {} // TODO: cmdBanTheirSorryAsses
void cmdGenComp(PCHAR szCmd) {} // TODO: cmdGenComp
void cmdKill(PCHAR szCmd) {} // TODO: cmdKill
void cmdSavePos(PCHAR szCmd) {} // TODO: cmdSavePos
void cmdCreateVehicle(PCHAR szCmd) {} // TODO: cmdCreateVehicle
void cmdSkin(PCHAR szCmd) {} // TODO: cmdSkin
void cmdBuild(PCHAR szCmd) {} // TODO: cmdBuild
void cmdMe(PCHAR szCmd) {} // TODO: cmdMe
void cmdMsg(PCHAR szCmd) {} // TODO: cmdMsg
void cmdSaveCoords(PCHAR szCmd) {} // TODO: cmdSaveCoords
void cmdBring(PCHAR szCmd) {} // TODO: cmdBring
void cmdGoto(PCHAR szCmd) {} // TODO: cmdGoto
void cmdSetCon(PCHAR szCmd) {} // TODO: cmdSetCon
void cmdSetHP(PCHAR szCmd) {} // TODO: cmdSetHP
void cmdSetArmour(PCHAR szCmd) {} // TODO: cmdSetArmour
void cmdSetMon(PCHAR szCmd) {} // TODO: cmdSetMon
void cmdSetWeap(PCHAR szCmd) {} // TODO: cmdSetWeap
void cmdSetLoc(PCHAR szCmd) {} // TODO: cmdSetLoc
void cmdDo(PCHAR szCmd) {} // TODO: cmdDo
void cmdLook(PCHAR szCmd) {} // TODO: cmdLook
void cmdAim(PCHAR szCmd) {} // TODO: cmdAim
void cmdWave(PCHAR szCmd) {} // TODO: cmdWave
void cmdBuy(PCHAR szCmd) {} // TODO: cmdBuy
void cmdSell(PCHAR szCmd) {} // TODO: cmdSell
void cmdFall(PCHAR szCmd) {} // TODO: cmdFall
void cmdHandsUp(PCHAR szCmd) {} // TODO: cmdHandsUp
void cmdSit(PCHAR szCmd) {} // TODO: cmdSit
void cmdStand(PCHAR szCmd) {} // TODO: cmdStand
void cmdActor(PCHAR szCmd) {} // TODO: cmdActor
void cmdActorOff(PCHAR szCmd) {} // TODO: cmdActorOff
void cmdZ(PCHAR szCmd) {} // TODO: cmdZ
void cmdDebug(PCHAR szCmd) {} // TODO: cmdDebug
void cmdCommand(PCHAR szCmd) {} // TODO: cmdCommand
void cmdSetMinute(PCHAR szCmd) {} // TODO: cmdSetMinute
void cmdSetHour(PCHAR szCmd) {} // TODO: cmdSetHour
void cmdSetWeather(PCHAR szCmd) {} // TODO: cmdSetWeather
void cmdSetTimeRate(PCHAR szCmd) {} // TODO: cmdSetTimeRate

//----------------------------------------------------

void SetupCommands()
{
	pCmdWindow->AddDefaultCmdProc(cmdDefaultCmdProc);
	pCmdWindow->AddCmdProc("quit",cmdQuit);
	pCmdWindow->AddCmdProc("q",cmdQuit);
	pCmdWindow->AddCmdProc("admin",cmdAdmin);
	pCmdWindow->AddCmdProc("kick",cmdKickEm);
	pCmdWindow->AddCmdProc("getip",cmdGetIP);
	pCmdWindow->AddCmdProc("banip",cmdBanIP);
	pCmdWindow->AddCmdProc("ban",cmdBanTheirSorryAsses);
	pCmdWindow->AddCmdProc("gencomp",cmdGenComp);
	pCmdWindow->AddCmdProc("kill",cmdKill);
	pCmdWindow->AddCmdProc("save",cmdSavePos);
	pCmdWindow->AddCmdProc("v",cmdCreateVehicle);
	pCmdWindow->AddCmdProc("vehicle",cmdCreateVehicle);
	pCmdWindow->AddCmdProc("skin",cmdSkin);
	pCmdWindow->AddCmdProc("build",cmdBuild);
	pCmdWindow->AddCmdProc("me",cmdMe);
	pCmdWindow->AddCmdProc("msg",cmdMsg);
	pCmdWindow->AddCmdProc("s",cmdSaveCoords);
	pCmdWindow->AddCmdProc("bring",cmdBring);
	pCmdWindow->AddCmdProc("goto",cmdGoto);
	pCmdWindow->AddCmdProc("setcon",cmdSetCon);
	pCmdWindow->AddCmdProc("sethp",cmdSetHP);
	pCmdWindow->AddCmdProc("setarm",cmdSetArmour);
	pCmdWindow->AddCmdProc("setmon",cmdSetMon);
	pCmdWindow->AddCmdProc("setwep",cmdSetWeap);
	pCmdWindow->AddCmdProc("setloc",cmdSetLoc);
	pCmdWindow->AddCmdProc("do",cmdDo);
	pCmdWindow->AddCmdProc("look",cmdLook);
	pCmdWindow->AddCmdProc("aim",cmdAim);
	pCmdWindow->AddCmdProc("wave",cmdWave);
	pCmdWindow->AddCmdProc("buy",cmdBuy);
	pCmdWindow->AddCmdProc("sell",cmdSell);
	pCmdWindow->AddCmdProc("fall",cmdFall);
	pCmdWindow->AddCmdProc("handsup",cmdHandsUp);
	pCmdWindow->AddCmdProc("sit", cmdSit);
	pCmdWindow->AddCmdProc("stand",cmdStand);
	pCmdWindow->AddCmdProc("actor",cmdActor);
	pCmdWindow->AddCmdProc("actoroff",cmdActorOff);
	pCmdWindow->AddCmdProc("z",cmdZ);
	pCmdWindow->AddCmdProc("debug",cmdDebug);
	pCmdWindow->AddCmdProc("command",cmdCommand);
	pCmdWindow->AddCmdProc("c",cmdCommand);
	pCmdWindow->AddCmdProc("setmin",cmdSetMinute);
	pCmdWindow->AddCmdProc("sethr",cmdSetHour);
	pCmdWindow->AddCmdProc("setweather",cmdSetWeather);
	pCmdWindow->AddCmdProc("settimerate",cmdSetTimeRate);
}

//----------------------------------------------------
