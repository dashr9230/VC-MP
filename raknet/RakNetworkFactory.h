
#ifndef __RAK_NETWORK_FACTORY_H
#define __RAK_NETWORK_FACTORY_H

#include "Export.h"

class RakClientInterface;
class RakServerInterface;

class RAK_DLL_EXPORT RakNetworkFactory
{
public:

	static RakClientInterface* GetRakClientInterface( void );
	static RakServerInterface* GetRakServerInterface( void );

	static void DestroyRakClientInterface( RakClientInterface* i );
	static void DestroyRakServerInterface( RakServerInterface* i );

};

#endif
