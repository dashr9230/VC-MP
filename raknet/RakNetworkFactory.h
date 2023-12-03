
#ifndef __RAK_NETWORK_FACTORY_H
#define __RAK_NETWORK_FACTORY_H

class RakServerInterface;

class RakNetworkFactory
{
public:
	static RakServerInterface* GetRakServerInterface( void );

	static void DestroyRakServerInterface( RakServerInterface* i );
};

#endif
