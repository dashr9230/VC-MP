
#pragma once
#ifndef VCMP_RCONCLIENT_H
#define VCMP_RCONCLIENT_H

class CRconClient
{
private:
	RakClientInterface* m_pRak;
public:
	CRconClient(char* szHostOrIp, int iPort, char* szPass);
	~CRconClient();

	bool IsConnected() { return m_pRak->IsConnected(); };

	void Command(char* szCommand);
	void Process();

	void Packet_ConnectionRequestAccepted(Packet* pPacket);
	void Packet_DisconnectionNotification(Packet* pPacket);
	void Packet_ConnectionLost(Packet* pPacket);
	void Packet_ConnectionBanned(Packet* pPacket);
	void Packet_NoFreeIncomingConnections(Packet* pPacket);
	void Packet_InvalidPassword(Packet* pPacket);
	void Packet_RconResponce(Packet* pPacket);
};

#endif
