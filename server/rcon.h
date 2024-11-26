
#ifndef VCMPSRV_RCON_H
#define VCMPSRV_RCON_H

class CRcon
{
private:
	RakServerInterface* m_pRak;
	int field_4[8];
public:

	CRcon(WORD iPort, char* szPass, WORD iMaxAdmins);
	~CRcon();

	void Process();

	void ConsoleOutput(char* szOutput);
	void ConsolePrintf( char* szFormat, ... );

	void Packet_NewIncomingConnection(Packet* pPacket);
	void Packet_DisconnectionNotification(Packet* pPacket);
	void Packet_ConnectionLost(Packet* pPacket);
	void Packet_RconCommand(Packet* pPacket);
};

#endif
