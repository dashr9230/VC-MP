
#ifndef __RAK_CLIENT_H
#define __RAK_CLIENT_H

#include "RakPeer.h"
#include "RakClientInterface.h"

class RakClient : public RakPeer, public RakClientInterface
{

public:

	bool Connect( const char* host, unsigned short serverPort, unsigned short clientPort, unsigned int depreciated, int threadSleepTimer );

	void Disconnect( unsigned int blockDuration, unsigned char orderingChannel=0 );

	void SetPassword( const char *_password );

	Packet* Receive( void );

	void DeallocatePacket( Packet *packet );

	void StartOccasionalPing( void );

	void RegisterAsRemoteProcedureCall( char* uniqueID, void ( *functionPointer ) ( RPCParameters *rpcParms ) );

	void UnregisterAsRemoteProcedureCall( char* uniqueID );

private:

};

#endif
