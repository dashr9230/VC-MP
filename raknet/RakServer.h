
#ifndef __RAK_SERVER_H
#define __RAK_SERVER_H

#include "RakServerInterface.h"

class RakServer : public RakServerInterface
{

public:

	bool Start( unsigned short AllowedPlayers, unsigned int depreciated, int threadSleepTimer, unsigned short port, const char *forceHostAddress=0 );

	void SetPassword( const char *_password );

	void SetAllowedPlayers( unsigned short AllowedPlayers );

	void UnregisterAsRemoteProcedureCall( char* uniqueID );
};

#endif
