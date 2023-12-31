
#ifndef _RCON_H_INCLUDED
#define _RCON_H_INCLUDED

class CRcon
{
private:
	RakServerInterface* m_pRak;
	int field_4[8];
public:

	CRcon(WORD iPort, char* szPass, WORD iMaxAdmins);
	~CRcon(void);

	void Process(void);

	void Packet_NewIncomingConnection(Packet* pPacket);
	void Packet_DisconnectionNotification(Packet* pPacket);
	void Packet_ConnectionLost(Packet* pPacket);
	void Packet_RconCommand(Packet* pPacket);
};

#endif
