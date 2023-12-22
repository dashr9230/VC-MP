
#ifndef __NETWORK_TYPES_H
#define __NETWORK_TYPES_H

#include "Export.h"

typedef unsigned short PlayerIndex;

/// \brief Unique identifier for a system.
/// Corresponds to a network address
struct RAK_DLL_EXPORT PlayerID
{
	///The peer address from inet_addr.
	unsigned int binaryAddress;
	///The port number
	unsigned short port;
};

struct Packet
{
	/// Server only - this is the index into the player array that this playerId maps to
	PlayerIndex playerIndex;

	/// The system that send this packet.
	PlayerID playerId;

	/// The length of the data in bytes
	/// \deprecated You should use bitSize.
	unsigned int length;

	char _padC[4];

	/// The data from the sender
	unsigned char* data;
};

/// All RPC functions have the same parameter list - this structure.
struct RPCParameters
{
	/// The data from the remote system
	unsigned char *input;

	/// How many bits long \a input is
	unsigned int numberOfBitsOfData;

	/// Which system called this RPC
	PlayerID sender;
};

/// \def REGISTER_STATIC_RPC
/// \ingroup RAKNET_RPC
/// Register a C function as a Remote procedure.
/// \param[in] networkObject Your instance of RakPeer, RakServer, or RakClient
/// \param[in] functionName The name of the C function to call
/// \attention 12/01/05 REGISTER_AS_REMOTE_PROCEDURE_CALL renamed to REGISTER_STATIC_RPC.  Delete the old name sometime in the future
//#pragma deprecated(REGISTER_AS_REMOTE_PROCEDURE_CALL)
//#define REGISTER_AS_REMOTE_PROCEDURE_CALL(networkObject, functionName) REGISTER_STATIC_RPC(networkObject, functionName)
#define REGISTER_STATIC_RPC(networkObject, functionName) (networkObject)->RegisterAsRemoteProcedureCall((#functionName),(functionName))

/// \def UNREGISTER_STATIC_RPC
/// \ingroup RAKNET_RPC
/// Unregisters a remote procedure call
/// RPC member Functions MUST be marked __cdecl!  See the ObjectMemberRPC example.
/// \param[in] networkObject The object that manages the function
/// \param[in] functionName The function name
// 12/01/05 UNREGISTER_AS_REMOTE_PROCEDURE_CALL Renamed to UNREGISTER_STATIC_RPC.  Delete the old name sometime in the future
//#pragma deprecated(UNREGISTER_AS_REMOTE_PROCEDURE_CALL)
//#define UNREGISTER_AS_REMOTE_PROCEDURE_CALL(networkObject,functionName) UNREGISTER_STATIC_RPC(networkObject,functionName)
#define UNREGISTER_STATIC_RPC(networkObject,functionName) (networkObject)->UnregisterAsRemoteProcedureCall((#functionName))


#endif

