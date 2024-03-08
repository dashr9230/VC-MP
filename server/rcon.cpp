
#include "main.h"
#include "rcon.h"
#include "../raknet/PacketEnumerations.h"

CRcon::CRcon(WORD iPort, char* szPass, WORD iMaxAdmins)
{
	m_pRak = RakNetworkFactory::GetRakServerInterface();
	m_pRak->SetPassword(szPass);
	if (!m_pRak->Start(iMaxAdmins, 0, 5, iPort))
	{
		logprintf("RCON: Unable to start Remote Console server.");
	} else {
		logprintf("RCON: Remote Console server started.");
	}
}

void CRcon::ConsoleOutput(char* szOutput)
{
	if (!m_pRak) return;

	BYTE bytePacketId = ID_RCON_RESPONSE;
	RakNet::BitStream bsResponce;
	bsResponce.Write(bytePacketId);
	DWORD dwRespLen = (DWORD)strlen(szOutput);
	bsResponce.Write(dwRespLen);
	bsResponce.Write(szOutput, dwRespLen);

	m_pRak->Send(&bsResponce, HIGH_PRIORITY, RELIABLE, 0, UNASSIGNED_PLAYER_ID, TRUE);
}

void CRcon::ConsolePrintf( char* szFormat, ... )
{
	char tmp_buf[2048];

	va_list args;
	va_start(args, szFormat);
	vsprintf(tmp_buf, szFormat, args);
	va_end(args);

	ConsoleOutput(tmp_buf);
}
