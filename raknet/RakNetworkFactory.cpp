
#include "RakNetworkFactory.h"
#include "RakServerInterface.h"
#include "RakServer.h"

RakServerInterface* RakNetworkFactory::GetRakServerInterface( void )
{
	return new RakServer;
}

void RakNetworkFactory::DestroyRakServerInterface( RakServerInterface* i )
{
	delete ( RakServer* ) i;
}