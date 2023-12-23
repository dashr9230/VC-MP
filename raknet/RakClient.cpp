
#include "RakClient.h"

bool RakClient::Connect( const char* host, unsigned short serverPort, unsigned short clientPort, unsigned int depreciated, int threadSleepTimer )
{
	// TODO: RakClient::Connect
	return false;
}

void RakClient::Disconnect( unsigned int blockDuration, unsigned char orderingChannel )
{
	// TODO: RakClient::Disconnect
}

void RakClient::SetPassword( const char *_password )
{
	// TODO: RakClient::SetPassword
}

Packet* RakClient::Receive( void )
{
	// TODO: RakClient::Receive

	return 0;
}

void RakClient::DeallocatePacket( Packet *packet )
{
	// TODO: RakClient::DeallocatePacket
}

void RakClient::StartOccasionalPing( void )
{
	// TODO: RakClient::StartOccasionalPing
}

void RakClient::RegisterAsRemoteProcedureCall( char* uniqueID, void ( *functionPointer ) ( RPCParameters *rpcParms ) )
{
	// TODO: RakClient::RegisterAsRemoteProcedureCall
}

void RakClient::UnregisterAsRemoteProcedureCall( char* uniqueID )
{
	// TODO: RakClient::UnregisterAsRemoteProcedureCall
}
