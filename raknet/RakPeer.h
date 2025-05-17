/* -*- mode: c++; c-file-style: raknet; tab-always-indent: nil; -*- */
/**
 * @file
 * @brief A RakPeer is the lower level Communication End Point. 
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
#ifndef __RAK_PEER_H
#define __RAK_PEER_H

#include "ReliabilityLayer.h"
#include "RakPeerInterface.h"

/**
 * @brief The lowest communication end point in RakNet.
 *
 * This class provide the lowest communication end point in RakNet.
 * It is recommended that you use it if you are going to be at the
 * same time client and server.
 */

class RakPeer : public RakPeerInterface
{

public:

	/**
	 * Fills the array remoteSystems with the playerID of all the systems we are connected to
	 *
	 * @param[out] remoteSystems  An array of PlayerID structures to be filled with the PlayerIDs of the systems we are connected to
	 * - pass 0 to remoteSystems to only get the number of systems we are connected to
	 * @param numberOfSystems As input, the size of remoteSystems array.  As output, the number of elements put into the array 
	 */
	bool GetConnectionList( PlayerID *remoteSystems, unsigned short *numberOfSystems ) const;

};

#endif
