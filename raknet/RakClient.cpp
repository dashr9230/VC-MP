
#include "RakClient.h"

// Constructor
RakClient::RakClient()
{
	unsigned i;

	for ( i = 0; i < 32; i++ )
		otherClients[ i ].isActive=false;

	field_A5C = 0;
}

void RakClient::InitializeSecurity( const char *privKeyP, const char *privKeyQ )
{
	RakPeer::InitializeSecurity( privKeyP, privKeyQ, 0, 0 );
}
