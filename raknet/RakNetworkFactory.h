
#ifndef __RAK_NETWORK_FACTORY_H
#define __RAK_NETWORK_FACTORY_H

class RakServerInterface;

class RakNetworkFactory
{
public:
	// Returns a new instance of the network server.
	static RakServerInterface* GetRakServerInterface(void);
};

#endif