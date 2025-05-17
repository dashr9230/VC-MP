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
#pragma pack(push,1)

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


	// TODO: struct PlayerID
};

#pragma pack(pop)

/**
 * @brief Network Packet
 *
 * This structure store information concerning
 * a packet going throught the network
 */
#pragma pack(push,1)

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

#endif
