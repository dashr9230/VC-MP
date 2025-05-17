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


	ID_CONNECTION_BANNED = 17,   //!< [PEER|CLIENT] We are banned from the system we attempted to connect to.
	ID_CONNECTION_REQUEST_ACCEPTED,   //!< [CLIENT] In a client/server enviroment, our connection request to the server has been accepted.

	ID_NO_FREE_INCOMING_CONNECTIONS = 20,   //!< [PEER|CLIENT] The system we attempted to connect to is not accepting new connections.
	ID_DISCONNECTION_NOTIFICATION,   //!< [PEER|SERVER|CLIENT] The system specified in Packet::playerID has disconnected from us.  For the client, this would mean the server has shutdown.
	ID_CONNECTION_LOST,   //!< [PEER|SERVER|CLIENT] Reliable packets cannot be delivered to the system specifed in Packet::playerID.  The connection to that system has been closed.

	ID_INVALID_PASSWORD = 25,   //!< [PEER|CLIENT] The remote system is using a password and has refused our connection because we did not set the correct password.

	ID_UPDATE_DISTRIBUTED_NETWORK_OBJECT = 29,   //!< [CLIENT|SERVER] Indicates creation or update of a distributed network object.  Pass to DistributedNetworkObjectManager::Instance()->HandleDistributedNetworkObjectPacket
	ID_DISTRIBUTED_NETWORK_OBJECT_CREATION_ACCEPTED,   //!< [CLIENT] Client creation of a distributed network object was accepted.  Pass to DistributedNetworkObjectManager::Instance()->HandleDistributedNetworkObjectPacketCreationAccepted
	ID_DISTRIBUTED_NETWORK_OBJECT_CREATION_REJECTED,   //!< [CLIENT] Client creation of a distributed network object was rejected.  Pass to DistributedNetworkObjectManager::Instance()->HandleDistributedNetworkObjectPacketCreationRejected

	// VC:MP 0.3z packets

	ID_PLAYER_SYNC = 48,
	ID_AIM_SYNC,
	ID_VEHICLE_SYNC,
	ID_PASSENGER_SYNC,
	ID_RCON_COMMAND,
	ID_RCON_RESPONSE,

};

#endif
