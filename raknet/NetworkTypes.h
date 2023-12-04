
#ifndef __NETWORK_TYPES_H
#define __NETWORK_TYPES_H

typedef unsigned short PlayerIndex;

struct PlayerID
{
	unsigned int binaryAddress;
	unsigned short port;
};

struct Packet
{
	PlayerIndex playerIndex;

	PlayerID playerId;

	char _gap0[8];

	unsigned char* data;
};

struct RPCParameters
{
	char _gap0;
};

#define REGISTER_AS_REMOTE_PROCEDURE_CALL(networkObject, functionName) (networkObject)->RegisterAsRemoteProcedureCall((#functionName),(functionName))

#define UNREGISTER_AS_REMOTE_PROCEDURE_CALL(networkObject,functionName) (networkObject)->UnregisterAsRemoteProcedureCall((#functionName))

#endif
