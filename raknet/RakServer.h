
#ifndef __RAK_SERVER_H
#define __RAK_SERVER_H

#include "RakPeer.h"
#include "RakServerInterface.h"
#include "Export.h"

class RAK_DLL_EXPORT RakServer : public RakServerInterface, public RakPeer
{

public:
	RakServer();

	bool Start( unsigned short AllowedPlayers, unsigned int depreciated, int threadSleepTimer, unsigned short port, const char *forceHostAddress=0 );

	void SetPassword( const char *_password );

	Packet* Receive( void );

	void DeallocatePacket( Packet *packet );

	void SetAllowedPlayers( unsigned short AllowedPlayers );

	void StartOccasionalPing( void );

	void RegisterAsRemoteProcedureCall( char* uniqueID, void ( *functionPointer ) ( RPCParameters *rpcParms ) );

	void UnregisterAsRemoteProcedureCall( char* uniqueID );

	void AddToBanList( const char *IP );

private:

};

#endif
