/* -*- mode: c++; c-file-style: raknet; tab-always-indent: nil; -*- */
/**
 * @file 
 * @brief Define the Structure of an Internal Packet 
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
#ifndef __INTERNAL_PACKET_H
#define __INTERNAL_PACKET_H

#include "SHA1.h"
#include "PacketPriority.h"

/**
 * This must be able to hold the highest value of RECEIVED_PACKET_LOG_LENGTH.
 */
typedef unsigned short PacketNumberType;

/**
* Use unsigned char for most apps.  Unsigned short if you send many packets at the same time on the same ordering stream
* This has to be the same value on all systems
*/
typedef unsigned char OrderingIndexType;

/**
 * @brief Structure of an Internal Packet
 * 
 * Internal packets are used whitin the RakNet Network Library for internal 
 * management only.
 */

struct InternalPacket
{
	/**
	 * True if this is an acknowledgement packet
	 */
	bool isAcknowledgement;
	/**
	 * The number of this packet, used as an identifier
	 */
	PacketNumberType packetNumber;
	/**
	 * The priority level of this packet
	 */
	PacketPriority priority;
	/**
	 * What type of reliability algorithm to use with this packet
	 */
	PacketReliability reliability;
	/**
	 * What ordering channel this packet is on, if the reliability type uses ordering channels
	 */
	unsigned char orderingChannel;
	/**
	 * The ID used as identification for ordering channels
	 */
	OrderingIndexType orderingIndex;
	/**
	 * The ID of the split packet, if we have split packets
	 */
	unsigned int splitPacketId;
	/**
	 * If this is a split packet, the index into the array of split packets
	 */
	unsigned int splitPacketIndex;
	/**
	 * The size of the array of split packets
	 */
	unsigned int splitPacketCount;
	/**
	 * When this packet was created
	 */
	unsigned int creationTime;
	/**
	 * The next time to take action on this packet
	 */
	unsigned int nextActionTime;
	/**
	 * How many bits the data is
	 */
	unsigned int dataBitLength;
	/**
	 * Buffer is a pointer to the actual data, assuming this packet has data at all
	 */
	char *data;
};

#endif

