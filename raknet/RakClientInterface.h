
#ifndef __RAK_CLIENT_INTERFACE_H
#define __RAK_CLIENT_INTERFACE_H

#include "NetworkTypes.h"

class RakClientInterface
{

public:

	virtual bool Connect( const char* host, unsigned short serverPort, unsigned short clientPort, unsigned int depreciated, int threadSleepTimer )=0;

	virtual void Disconnect( unsigned int blockDuration, unsigned char orderingChannel=0 )=0;

	virtual void SetPassword( const char *_password )=0;

	virtual Packet* Receive( void )=0;

	virtual void DeallocatePacket( Packet *packet )=0;

	virtual void StartOccasionalPing( void )=0;

	virtual void RegisterAsRemoteProcedureCall( char* uniqueID, void ( *functionPointer ) ( RPCParameters *rpcParms ) )=0;

	virtual void UnregisterAsRemoteProcedureCall( char* uniqueID )=0;

};

#endif
