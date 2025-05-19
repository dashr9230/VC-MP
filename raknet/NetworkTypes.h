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

#endif
