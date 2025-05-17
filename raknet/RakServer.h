/* -*- mode: c++; c-file-style: raknet; tab-always-indent: nil; -*- */
/**
 * @file
 * @brief A RakServer provide Server facilities 
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

#ifndef __RAK_SERVER_H
#define __RAK_SERVER_H

#include "RakPeer.h"
#include "RakServerInterface.h"

/**
 * @brief Server Facilities on top of RakPeer
 *
 * This class provide an increase level of services on top of
 * RakPeer. The communication end point can now only accept connexion
 * and exchange message with peer connected to him 
 *
 *@see RakClient
 * 
 */

class RakServer : public RakServerInterface, public RakPeer
{

public:

	/**
	 * This function only works while the server is active (Use the Start function).  Returns false on failure, true on success
	 * Send the bitstream to whichever playerId you specify.
	 * You can set the first byte to a packet identifier, however you will need to have TYPE_CHECKING undefined or the internal type checking
	 * will add extra data and make this not work.  If you want TYPE_CHECKING on, you will need to use BitStream::WriteBits to avoid the type checking.
	 * This interface will probably change to fix this in future versions.
	 * If you aren't sure what to specify for priority and reliability, use HIGH_PRIORITY and RELIABLE, 0 for ordering channel
	 * Set broadcast to true to broadcast to all connected clients EXCEPT the one specified in the playerId field.
	 * To broadcast to everyone specify UNASSIGNED_PLAYER_ID for the playerId field.
	 */
	bool Send( RakNet::BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, PlayerID playerId, bool broadcast );

	/**
	 * Return how many players are allowed to connect. This value was set either from Start or from SetAllowedPlayers
	 * The server must be active for this to have meaning
	 */
	unsigned short GetAllowedPlayers( void ) const;

	/**
	 * Returns true if the server is currently active
	 */
	bool IsActive( void ) const;

	/**
	 * This function is only useful for looping through all players.
	 * Index should range between 0 and the maximum number of players allowed - 1.
	 */
	PlayerID GetPlayerIDFromIndex( int index );

private:

};

#endif
