/* -*- mode: c++; c-file-style: raknet; tab-always-indent: nil; -*- */
/**
 * @file NetworkTypes.h
 * @brief Define Network Common Class and Types.
 *
 * This file is part of RakNet Copyright 2003, 2004 Rakkarsoft LLC and
 * Kevin Jenkins.
 *
 * Usage of Raknet is subject to the appropriate licence agreement.
 * "Shareware" Licensees with Rakkarsoft LLC are subject to the
 * shareware license found at
 * http://www.rakkarsoft.com/shareWareLicense.html which you agreed to
 * upon purchase of a "Shareware license" "Commercial" Licensees with
 * Rakkarsoft LLC are subject to the commercial license found at
 * http://www.rakkarsoft.com/sourceCodeLicense.html which you agreed
 * to upon purchase of a "Commercial license" All other users are
 * subject to the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * Refer to the appropriate license agreement for distribution,
 * modification, and warranty rights.
 */

#ifndef __NETWORK_TYPES_H
#define __NETWORK_TYPES_H
/**
 * Typename for Network Object Identifier
 */
typedef unsigned short ObjectID;

/**
 * Typename for player index
 */
typedef unsigned short PlayerIndex;

/**
 * @brief Player Identifier
 *
 * This define a Player Unique Identifier.
 * In fact, it corresponds to the peer address.
 */
#pragma pack(1)
struct PlayerID
{
	/**
	 * The peer address from inet_addr.
	 */
	unsigned int binaryAddress;
	/**
	 * The port number associated to the connexion.
	 */
	unsigned short port;

	/**
	 * Copy operator
	 * @param input a player ID
	 * @return a reference to the current object
	 */
#ifdef _WIN32
	PlayerID& PlayerID::operator = ( const PlayerID& input )
	{
		binaryAddress = input.binaryAddress;
		port = input.port;
		return *this;
	}
#endif

	/**
	 * Test if two Player Unique Identifier are the same
	 * @param left a Player Unique Identifier
	 * @param right a Player Unique Identifier
	 * @return 1 if left and right corresponds to the same player 0 otherwise
	 */
	friend int operator==( const PlayerID& left, const PlayerID& right );

	/**
	 * Test if two Player Unique Identifier differs
	 * @param left a Player Unique Identifier
	 * @param right a Player Unique Identifier
	 * @return 0 if left and right corresponds to the same player 1 otherwise
	 */
	friend int operator!=( const PlayerID& left, const PlayerID& right );
};


/**
 * @brief Connection request handling
 *
 * This structure is used internaly to store the connection request
 * @internal
 */

struct RequestedConnectionStruct
{
	/**
	 * Who we wanted to connect to.
	 */
	PlayerID playerId;
	/**
	 * When will we requested this connection.
	 */
	unsigned int time;
	/**
	 * Security key
	 */
	unsigned char AESKey[ 16 ];
	/**
	 * true if security policy are enabled
	 */
	bool setAESKey;
	/**
	 * Next time we will try to connect
	 */
	unsigned int nextRequestTime;
};

/**
 * @brief Network Packet
 *
 * This structure store information concerning
 * a packet going throught the network
 */

struct Packet
{
	/**
	 * Server only - this is the index into the player array that this playerId maps to
	 */
	PlayerIndex playerIndex;
	/**
	 * The Player Unique Identifier that send this packet.
	 */
	PlayerID playerId;
	/**
	 * The length of the data.
	 * @deprecated You should use bitSize inplace.
	 *
	 */
	unsigned int length;
	/**
	 * The number of bits in used.
	 * Same as length but represents bits. Length is obsolete and retained for backwards compatibility.
	 */
	unsigned int bitSize;
	/**
	 * The byte array.
	 * The standard behaviour in RakNet define the first byte of the data array as the packet class.
	 * @see PacketEnumerations.h
	 */
	unsigned char* data;
};

/**
 * @brief Store Accepted Connection
 *
 * Handle active connection.
 * @internal
 */
#pragma pack(push,1)
#pragma pack(1)

struct ConnectionAcceptStruct
{
	/**
	 *
	 */
	unsigned char typeId;
	/**
	 * peer port
	 */
	unsigned short remotePort;
	/**
	 * We tell the remote system its own IP / port this way
	 */
	PlayerID externalID;
	/**
	 * Index of the player
	 */
	PlayerIndex playerIndex;
};

/**
 * @brief Store Ping informations
 * Handle Pinging operations
 * @internal
 */
#pragma pack(1)

struct PingStruct
{
	/**
	 * ID_PING or ID_PONG
	 */
	unsigned char typeId;
	/**
	 * Limit for sending next ping packet
	 */
	unsigned int sendPingTime;
	/**
	 * Limit for sending next pong packet
	 */
	unsigned int sendPongTime;
};

/**
 * @brief Store Unconnected ping informations
 *
 * @internal
 */
#pragma pack(1)

struct UnconnectedPingStruct
{
	/**
	 * ID_PING or ID_PONG
	 */
	unsigned char typeId;
	/**
	 *
	 */
	unsigned int sendPingTime;
};

/**
 * @brief Synchronized Random Number
 * Timestamp automatically used for this type of packet
 * @internal
 */
#pragma pack(1)

struct SetRandomNumberSeedStruct
{
	/**
	 * ID_TIMESTAMP
	 */
	unsigned char ts;
	/**
	 * Timestamp value
	 */
	unsigned int timeStamp;
	/**
	 * ID_SET_RANDOM_NUMBER_SEED
	 */
	unsigned char typeId;
	/**
	 * Seed value
	 */
	unsigned int seed;
	/**
	 * NextSeed value
	 */
	unsigned int nextSeed;
};

/**
 * @brief Incoming Connection
 * Manage incoming connection
 *
 * @internal
 */
#pragma pack(1)

struct NewIncomingConnectionStruct
{
	/**
	 * ID_NEW_INCOMING_CONNECTION
	 */
	unsigned char typeId;
	/**
	 * We tell the remote system its own IP / port this way
	 */
	PlayerID externalID;
};

#pragma pack(pop)

/**
 * Index of an invalid Player Unique Id
 */
const PlayerID UNASSIGNED_PLAYER_ID =
	{
		0xFFFFFFFF, 0xFFFF
	};

/**
 * Invalid Object Unique Id
 */
const ObjectID UNASSIGNED_OBJECT_ID = 65535;

/**
 * Sizeof the Ping Array
 */
const int PING_TIMES_ARRAY_SIZE = 5;

/**
 * @defgroup RAKNET_RPC Remote Procedure Call Subsystem.
 * @brief RPC Function Implementation
 *
 * The Remote Procedure Call Subsystem provide the RPC paradigm to
 * RakNet user. It consists in providing remote function call over the
 * network.  A call to a remote function require you to prepare the
 * data for each parameter (using BitStream) for example.
 *
 *
 * Use the following C function prototype for your callbacks
 * @code
 * void functionName(char *input, int numberOfBitsOfData, PlayerID sender);
 * @encode
 * If you pass input data, you can parse the input data in two ways.
 *
 * 1.
 * Cast input to a struct (such as if you sent a struct)
 * i.e. MyStruct *s = (MyStruct*) input;
 * Make sure that the sizeof(MyStruct) is equal to the number of bytes passed!
 *
 * 2.
 * Create a BitStream instance with input as data and the number of bytes
 * i.e. BitStream myBitStream(input, (numberOfBitsOfData-1)/8+1)
 *
 * (numberOfBitsOfData-1)/8+1 is how convert from bits to bytes
 *
 * Full example:
 * @code
 * void MyFunc(char *input, int numberOfBitsOfData, PlayerID sender) {}
 * RakClient *rakClient;
 * REGISTER_AS_REMOTE_PROCEDURE_CALL(rakClient, MyFunc);
 * This would allow MyFunc to be called from the server using  (for example)
 * rakServer->RPC("MyFunc", 0, clientID, false);
 * @endocde
 */

/**
 * @def REGISTER_AS_REMOTE_PROCEDURE_CALL
 * @ingroup RAKNET_RPC
 * Register a C function as a Remote procedure.
 * @param networkObject The object that will handle the remote procedure call
 * @param functionName The name of the function
 */
#define REGISTER_AS_REMOTE_PROCEDURE_CALL(networkObject, functionName) (networkObject)->RegisterAsRemoteProcedureCall((#functionName),(functionName))

/**
 * @def UNREGISTER_AS_REMOTE_PROCEDURE_CALL
 * @ingroup RAKNET_RPC
 * Unregisters a remote procedure call
 * @param networkObject The that manage the function
 * @param functionName The function name
 */
#define UNREGISTER_AS_REMOTE_PROCEDURE_CALL(networkObject,functionName) (networkObject)->UnregisterAsRemoteProcedureCall((#functionName))

#endif
