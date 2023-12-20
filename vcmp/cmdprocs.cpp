
#include "main.h"

extern CCmdWindow	 *pCmdWindow;

//----------------------------------------------------

void WriteCompression(ULONG *ulWrite)
{
	FILE *fileComp=fopen("ClientLayer.txt","w");

	int x=0;

	while(x!=256) {
		fprintf(fileComp,"0x%X,",ulWrite[x]);
		x++;
	}

	fclose(fileComp);
}

//----------------------------------------------------

void IP2String(DWORD ip, char *ret)
{
	BYTE p[4];

	p[0] = (BYTE)(ip & 0xFF); ip >>= 8;
	p[1] = (BYTE)(ip & 0xFF); ip >>= 8;	
	p[2] = (BYTE)(ip & 0xFF); ip >>= 8;
	p[3] = (BYTE)(ip & 0xFF);

	sprintf(ret,"%u.%u.%u.%u",p[0],p[1],p[2],p[3]);
}

//----------------------------------------------------

void cmdActor(PCHAR szCmd)
{
	// nothing
}

//----------------------------------------------------

void cmdActorOff(PCHAR szCmd)
{
	// nothing
}

//----------------------------------------------------

void cmdZ(PCHAR szCmd)
{
	// nothing
}

//----------------------------------------------------

void cmdDebug(PCHAR szCmd) {} // TODO
void cmdDefaultCmdProc(PCHAR szCmd) {} // TODO
void cmdQuit(PCHAR szCmd) {} // TODO
void cmdKill(PCHAR szCmd) {} // TODO
void cmdSavePos(PCHAR szCmd) {} // TODO
void cmdCreateVehicle(PCHAR szCmd) {} // TODO
void cmdSkin(PCHAR szCmd) {} // TODO
void cmdBuild(PCHAR szCmd) {} // TODO
void cmdAdmin(PCHAR szCmd) {} // TODO
void cmdKickEm(PCHAR szCmd) {} // TODO
void cmdBanIP(PCHAR szCmd) {} // TODO
void cmdBanTheirSorryAsses(PCHAR szCmd) {} // TODO
void cmdGetIP(PCHAR szCmd) {} // TODO
void cmdSaveCoords(PCHAR szCmd) {} // TODO
void cmdMe(PCHAR szCmd) {} // TODO
void cmdMsg(PCHAR szCmd) {} // TODO
void cmdBring(PCHAR szCmd) {} // TODO
void cmdGoto(PCHAR szCmd) {} // TODO
void cmdSetCon(PCHAR szCmd) {} // TODO
void cmdSetHP(PCHAR szCmd) {} // TODO
void cmdSetArm(PCHAR szCmd) {} // TODO
void cmdSetMon(PCHAR szCmd) {} // TODO
void cmdSetWep(PCHAR szCmd) {} // TODO
void cmdSet(PCHAR szCmd) {} // TODO
void cmdSetLoc(PCHAR szCmd) {} // TODO
void cmdDo(PCHAR szCmd) {} // TODO
void cmdLook(PCHAR szCmd) {} // TODO
void cmdAim(PCHAR szCmd) {} // TODO
void cmdWave(PCHAR szCmd) {} // TODO
void cmdBuy(PCHAR szCmd) {} // TODO
void cmdSell(PCHAR szCmd) {} // TODO
void cmdFall(PCHAR szCmd) {} // TODO
void cmdHandsUp(PCHAR szCmd) {} // TODO
void cmdSit(PCHAR szCmd) {} // TODO
void cmdStand(PCHAR szCmd) {} // TODO
void cmdCommand(PCHAR szCmd) {} // TODO
void cmdSetMin(PCHAR szCmd) {} // TODO
void cmdSetHr(PCHAR szCmd) {} // TODO
void cmdSetWeather(PCHAR szCmd) {} // TODO
void cmdSetTimeRate(PCHAR szCmd) {} // TODO
void cmdSpike(PCHAR szCmd) {} // TODO

void cmdGenComp(PCHAR szCmd)
{
	// nothing
}

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
	pCmdWindow->AddCmdProc("setarm",cmdSetArm);
	pCmdWindow->AddCmdProc("setmon",cmdSetMon);
	pCmdWindow->AddCmdProc("setwep",cmdSetWep);
	pCmdWindow->AddCmdProc("setloc",cmdSetLoc);
	pCmdWindow->AddCmdProc("do",cmdDo);
	pCmdWindow->AddCmdProc("look",cmdLook);
	pCmdWindow->AddCmdProc("aim",cmdAim);
	pCmdWindow->AddCmdProc("wave",cmdWave);
	pCmdWindow->AddCmdProc("buy",cmdBuy);
	pCmdWindow->AddCmdProc("sell",cmdSell);
	pCmdWindow->AddCmdProc("fall",cmdFall);
	pCmdWindow->AddCmdProc("handsup",cmdHandsUp);
	pCmdWindow->AddCmdProc("sit",cmdSit);
	pCmdWindow->AddCmdProc("stand",cmdStand);
	pCmdWindow->AddCmdProc("actor",cmdActor);
	pCmdWindow->AddCmdProc("actoroff",cmdActorOff);
	pCmdWindow->AddCmdProc("z",cmdZ);
	pCmdWindow->AddCmdProc("debug",cmdDebug);
	pCmdWindow->AddCmdProc("command",cmdCommand);
	pCmdWindow->AddCmdProc("c",cmdCommand);
	pCmdWindow->AddCmdProc("set",cmdSet);
	pCmdWindow->AddCmdProc("setmin",cmdSetMin);
	pCmdWindow->AddCmdProc("sethr",cmdSetHr);
	pCmdWindow->AddCmdProc("setweather",cmdSetWeather);
	pCmdWindow->AddCmdProc("settimerate",cmdSetTimeRate);
	pCmdWindow->AddCmdProc("spike",cmdSpike);
}

//----------------------------------------------------