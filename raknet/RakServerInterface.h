
#ifndef __RAK_SERVER_INTERFACE_H
#define __RAK_SERVER_INTERFACE_H

#include "NetworkTypes.h"
#include "Export.h"

class RAK_DLL_EXPORT RakServerInterface
{

public:

	virtual bool Start( unsigned short AllowedPlayers, unsigned int depreciated, int threadSleepTimer, unsigned short port, const char *forceHostAddress=0 )=0;

	virtual void SetPassword( const char *_password )=0;

	virtual Packet* Receive( void )=0;

	virtual void DeallocatePacket( Packet *packet )=0;

	virtual void SetAllowedPlayers( unsigned short AllowedPlayers )=0;

	virtual void StartOccasionalPing( void )=0;

	virtual void RegisterAsRemoteProcedureCall( char* uniqueID, void ( *functionPointer ) ( RPCParameters *rpcParms ) )=0;

	virtual void UnregisterAsRemoteProcedureCall( char* uniqueID )=0;

	virtual void AddToBanList( const char *IP )=0;

};

#endif
