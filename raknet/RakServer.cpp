
#include "RakServer.h"

bool RakServer::Start( unsigned short AllowedPlayers, unsigned int depreciated, int threadSleepTimer, unsigned short port, const char *forceHostAddress )
{
	// TODO: RakServer::Start

	return false;
}

void RakServer::SetPassword( const char *_password )
{
	// TODO: RakServer::SetPassword
}

Packet* RakServer::Receive( void )
{
	// TODO: RakServer::Receive

	return 0;
}

void RakServer::DeallocatePacket( Packet *packet )
{
	// TODO: RakServer::DeallocatePacket
}

void RakServer::SetAllowedPlayers( unsigned short AllowedPlayers )
{
	// TODO: RakServer::SetAllowedPlayers
}

void RakServer::RegisterAsRemoteProcedureCall( char* uniqueID, void ( *functionPointer ) ( RPCParameters *rpcParms ) )
{
	// TODO: RakServer::RegisterAsRemoteProcedureCall
}

void RakServer::UnregisterAsRemoteProcedureCall( char* uniqueID )
{
	// TODO: RakServer::UnregisterAsRemoteProcedureCall
}

void RakServer::AddToBanList( const char *IP )
{
	// TODO: RakServer::AddToBanList
}
