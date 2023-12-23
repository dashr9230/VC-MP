
#include "RakNetworkFactory.h"
#include "RakServerInterface.h"
#include "RakClientInterface.h"
#include "RakServer.h"
#include "RakClient.h"

RakClientInterface* RakNetworkFactory::GetRakClientInterface( void )
{
	return new RakClient;
}
RakServerInterface* RakNetworkFactory::GetRakServerInterface( void )
{
	return new RakServer;
}

void RakNetworkFactory::DestroyRakClientInterface( RakClientInterface* i )
{
	delete ( RakClient* ) i;
}
void RakNetworkFactory::DestroyRakServerInterface( RakServerInterface* i )
{
	delete ( RakServer* ) i;
}
