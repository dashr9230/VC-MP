/* -*- mode: c++; c-file-style: raknet; tab-always-indent: nil; -*- */
/**
 * @ingroup RALNET_MESSAGE_ID
 * @file 
 * @brief Define RakNet internal packet identifier 
 *
 * This file is part of RakNet Copyright 2003, 2004
 * Rakkarsoft LLC and Kevin Jenkins.
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
#ifndef __PACKET_ENUMERATIONS_H
#define __PACKET_ENUMERATIONS_H 
/**
 * @defgroup RAKNET_MESSAGE_ID Message Identifier 
 * 
 * You should not edit the file PacketEnumerations.h as it is a part of RakNet static library
 * To define your own message id, define an enum following the code example that follows. 
 *
 * @code
 * enum {
 *   ID_MYPROJECT_MSG_1 = ID_RESERVERD_9 + 1, 
 *   ID_MYPROJECT_MSG_2, 
 *    ... 
 * };
 * @endcode 
 *
 * @note RakNet define message ID as a 1 byte information. If you
 * require more than 256 message IDs do not reuse the function
 * Multiplayer::GetPacketIdentifier and replace the existing one by a
 * correct version of this function the version. In this case you can
 * integrate in the code of your project the file Multiplayer.h and
 * edit this file to fits your needs.
 */

enum {
	//
	// RESERVED TYPES - DO NOT CHANGE THESE
	//
	// Ignore these:
	ID_PING,   //!< Ping (internal use only)
	ID_PING_OPEN_CONNECTIONS,   //!< Only reply to the unconnected ping if we have open connections
	ID_REQUEST_STATIC_DATA,   //!< Someone asked for our static data (internal use only)
	ID_CONNECTION_REQUEST,   //!< Asking for a new connection (internal use only)
	ID_SECURED_CONNECTION_RESPONSE,   //!< Connecting to a secured server/peer
	ID_SECURED_CONNECTION_CONFIRMATION,   //!< Connecting to a secured server/peer
	ID_RPC,   //!< Remote procedure call (internal use only)
	ID_BROADCAST_PINGS,   //!< Server / Client only - The server is broadcasting the pings of all players in the game (internal use only)
	ID_SET_RANDOM_NUMBER_SEED,   //!< Server / Client only - The server is broadcasting a random number seed (internal use only)
	ID_RPC_WITH_TIMESTAMP,   //!< Same as RPC, but treat the first 4 bytes as a timestamp
	//Handle these below.  Possible recipients in [...]
	ID_PONG,   //!< [CLIENT|PEER] Pong.  Returned if we ping a system we are not connected so.  First byte is ID_PONG, second 4 bytes is the ping, following bytes is system specific enumeration data.
	ID_RSA_PUBLIC_KEY_MISMATCH,   //!< [CLIENT|PEER] We preset an RSA public key which does not match what the system we connected to is using.
	ID_REMOTE_DISCONNECTION_NOTIFICATION,   //!< [CLIENT] In a client/server enviroment, a client other than ourselves has disconnected gracefully.  Packet::playerID is modified to reflect the playerID of this client.
	ID_REMOTE_CONNECTION_LOST,   //!< [CLIENT] In a client/server enviroment, a client other than ourselves has been forcefully dropped. Packet::playerID is modified to reflect the playerID of this client.
	ID_REMOTE_NEW_INCOMING_CONNECTION,   //!< [CLIENT] In a client/server enviroment, a client other than ourselves has connected.  Packet::playerID is modified to reflect the playerID of this client.
	ID_REMOTE_EXISTING_CONNECTION,   //!< [CLIENT] On our initial connection to the server, we are told of every other client in the game.  Packet::playerID is modified to reflect the playerID of this client.
	ID_REMOTE_STATIC_DATA,   //!< [CLIENT] - Got the data for another client
	ID_CONNECTION_BANNED,   //!< [PEER|CLIENT] We are banned from the system we attempted to connect to.
	ID_CONNECTION_REQUEST_ACCEPTED,   //!< [CLIENT] In a client/server enviroment, our connection request to the server has been accepted.
	ID_NEW_INCOMING_CONNECTION,   //!< [PEER|SERVER] A remote system has successfully connected.
	ID_NO_FREE_INCOMING_CONNECTIONS,   //!< [PEER|CLIENT] The system we attempted to connect to is not accepting new connections.
	ID_DISCONNECTION_NOTIFICATION,   //!< [PEER|SERVER|CLIENT] The system specified in Packet::playerID has disconnected from us.  For the client, this would mean the server has shutdown.
	ID_CONNECTION_LOST,   //!< [PEER|SERVER|CLIENT] Reliable packets cannot be delivered to the system specifed in Packet::playerID.  The connection to that system has been closed.
	ID_TIMESTAMP,   //!< [PEER|SERVER|CLIENT] The four bytes following this byte represent an unsigned int which is automatically modified by the difference in system times between the sender and the recipient. Requires that you call StartOccasionalPing.
	ID_RECEIVED_STATIC_DATA,   //!< [PEER|SERVER|CLIENT] We got a bitstream containing static data.  You can now read this data. This packet is transmitted automatically on connections, and can also be manually sent.
	ID_INVALID_PASSWORD,   //!< [PEER|CLIENT] The remote system is using a password and has refused our connection because we did not set the correct password.
	ID_MODIFIED_PACKET,   //!< [PEER|SERVER|CLIENT] A packet has been tampered with in transit.  The sender is contained in Packet::playerID.
	ID_REMOTE_PORT_REFUSED,   //!< [PEER|SERVER|CLIENT] The remote host is not accepting data on this port.  This only comes up when connecting to yourself on the same computer and there is no bound socket on that port.

	ID_UPDATE_DISTRIBUTED_NETWORK_OBJECT = 29,   //!< [CLIENT|SERVER] Indicates creation or update of a distributed network object.  Pass to DistributedNetworkObjectManager::Instance()->HandleDistributedNetworkObjectPacket
	ID_DISTRIBUTED_NETWORK_OBJECT_CREATION_ACCEPTED,   //!< [CLIENT] Client creation of a distributed network object was accepted.  Pass to DistributedNetworkObjectManager::Instance()->HandleDistributedNetworkObjectPacketCreationAccepted
	ID_DISTRIBUTED_NETWORK_OBJECT_CREATION_REJECTED,   //!< [CLIENT] Client creation of a distributed network object was rejected.  Pass to DistributedNetworkObjectManager::Instance()->HandleDistributedNetworkObjectPacketCreationRejected

	ID_ADVERTISE_SYSTEM = 42,   //!< [PEER|SERVER|CLIENT] Inform a remote system of our IP/Port.

	// VC:MP 0.3z packets

	ID_PLAYER_SYNC = 48,
	ID_AIM_SYNC,
	ID_VEHICLE_SYNC,
	ID_PASSENGER_SYNC,
	ID_RCON_COMMAND,
	ID_RCON_RESPONSE,

};

#endif
