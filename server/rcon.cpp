
#include "main.h"

extern char *szAdminPass;

CRcon::CRcon(WORD iPort, char* szPass, WORD iMaxAdmins)
{
	m_pRak = RakNetworkFactory::GetRakServerInterface();
	m_pRak->SetPassword(szPass);
	szAdminPass = szPass;

	for(int i=0; i<8; i++) {
		field_4[i] = 0;
	}

	if (!m_pRak->Start(iMaxAdmins, 0, 5, iPort))
	{
		logprintf("RCON: Unable to start Remote Console server.");
	} else {
		logprintf("RCON: Remote Console server started.");
	}
}

CRcon::~CRcon()
{
	if (m_pRak)
		RakNetworkFactory::DestroyRakServerInterface(m_pRak);
}

void CRcon::Process(void)
{
	if (!m_pRak)
		return;

	Packet* pPacket;
	while(pPacket = m_pRak->Receive())
	{
		switch (pPacket->data[0])
		{
		case ID_NEW_INCOMING_CONNECTION:
			Packet_NewIncomingConnection(pPacket);
			break;
		case ID_DISCONNECTION_NOTIFICATION:
			Packet_DisconnectionNotification(pPacket);
			break;
		case ID_CONNECTION_LOST:
			Packet_ConnectionLost(pPacket);
			break;
		case ID_RCON_COMMAND:
			Packet_RconCommand(pPacket);
			break;
		}
		m_pRak->DeallocatePacket(pPacket);
	}
}

void CRcon::Packet_NewIncomingConnection(Packet* pPacket)
{
	field_4[pPacket->playerIndex] = 0;
	in_addr in;
	in.s_addr = pPacket->playerId.binaryAddress;
	logprintf("RCON: Admin [%s] has connected.", inet_ntoa(in));
	printf("RCON: Admin [%s] has connected.\n", inet_ntoa(in));
}

void CRcon::Packet_DisconnectionNotification(Packet* pPacket)
{
	field_4[pPacket->playerIndex] = 0;
	in_addr in;
	in.s_addr = pPacket->playerId.binaryAddress;
	logprintf("RCON: Admin [%s] has disconnected.", inet_ntoa(in));
	printf("RCON: Admin [%s] has disconnected.\n", inet_ntoa(in));
}

void CRcon::Packet_ConnectionLost(Packet* pPacket)
{
	field_4[pPacket->playerIndex] = 0;
	in_addr in;
	in.s_addr = pPacket->playerId.binaryAddress;
	logprintf("RCON: Admin [%s] has lost connection.", inet_ntoa(in));
	printf("RCON: Admin [%s] has lost connection.\n", inet_ntoa(in));
}

void CRcon::Packet_RconCommand(Packet* pPacket)
{
	// TODO: CRcon::Packet_RconCommand
}
