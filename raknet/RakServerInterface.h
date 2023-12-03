
#ifndef __RAK_SERVER_INTERFACE_H
#define __RAK_SERVER_INTERFACE_H

#include "NetworkTypes.h"

class RakServerInterface
{

public:

	virtual bool Start( unsigned short AllowedPlayers, unsigned int depreciated, int threadSleepTimer, unsigned short port, const char *forceHostAddress=0 )=0;

	virtual void SetPassword( const char *_password )=0;

	virtual void SetAllowedPlayers( unsigned short AllowedPlayers )=0;

	virtual void UnregisterAsRemoteProcedureCall( char* uniqueID )=0;
};

#endif
