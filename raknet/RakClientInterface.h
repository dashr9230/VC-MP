/* -*- mode: c++; c-file-style: raknet; tab-always-indent: nil; -*- */
/**
 * @file 
 * @brief User view of a RakClient object. 
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
#ifndef __RAK_CLIENT_INTERFACE_H
#define __RAK_CLIENT_INTERFACE_H

#include "NetworkTypes.h"
#include "PacketPriority.h"
#include "BitStream.h"

/**
 * @brief Define user point of vue of a RakClient communication end point.
 * 
 * This class define the user view of a RakClient communication
 * end-point. All accessible operation are available in this class.
 * You should only deal with RakClient object throught instance of
 * RakClientInterface.
 */

class RakClientInterface
{

public:

	/**
	 * Call this to connect the client to the specified host (ip or domain name) and server port.
	 * This is a non-blocking connection.  You know the connection is successful when IsConnected() returns true
	 * or receive gets a packet with the type identifier ID_CONNECTION_REQUEST_ACCEPTED.
	 * serverPort is which port to connect to on the remote machine. clientPort is the port you want the 
	 * client to use. Both ports must be open for UDP
	 *
	 * @param host a hostname 
	 * @param serverPort The port on which to contact @em host 
	 * @param clientPort The port to use localy 
	 * @param connectionValidationInteger is legacy and unused
	 * @param threadSleepTimer >=0 for how many ms to Sleep each internal update cycle 
	 * (recommended 30 for low performance, 0 for regular)
	 * @return true on successful initiation, false otherwise
	 */
	virtual bool Connect( char* host, unsigned short serverPort, unsigned short clientPort, unsigned int connectionValidationInteger, int threadSleepTimer ) = 0;
	/**
	 * Stops the client, stops synchronized data, and resets all internal data. 
	 * Does nothing if the client is not connected to begin with
	 * blockDuration is how long you should wait for all remaining packets to go out
	 * If you set it to 0 then the disconnection notification probably won't arrive
	 * @param blockDuration The time to wait before truly close the communication and point
	 */
	virtual void Disconnect( unsigned int blockDuration ) = 0;

	/**
	 * Set the password to use when connecting to a server.  The password persists between connections.
	 * Pass 0 for no password.
	 * @param _password The password to use to connect to a server 
	 */
	virtual void SetPassword( char *_password ) = 0;



	/**
	 * This function only works while the client is connected (Use the
	 * Connect function).  Returns false on failure, true on success
	 * Sends the BitStream If you aren't sure what to specify for
	 * priority and reliability, use HIGH_PRIORITY and RELIABLE, 0 for
	 * ordering channel
	 * @param bitstream the data to send. 
	 * @param priority the priority of the message 
	 * @param reliability the reliability policy required 
	 * @param orderingChannel the channel to send the message to. 
	 */
	virtual bool Send( RakNet::BitStream * bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel ) = 0;
	/**
	 * Call this to get a packet from the incoming packet queue. Use
	 * DeallocatePacket to deallocate the packet after you are done with
	 * it.  Check the Packet struct at the top of
	 * CoreNetworkStructures.h for the format of the struct Returns 0 if
	 * no packets are waiting to be handled If the client is not active
	 * this will also return 0, as all waiting packets are flushed when
	 * the client is Disconnected This also updates all memory blocks
	 * associated with synchronized memory
	 * @return the last receive packet 
	 */
	virtual Packet* Receive( void ) = 0;
	/**
	 * Call this to deallocate a packet returned by Receive when you are done handling it.
	 * Free the memory associated to a packet. It is not the same as using delete operator because 
	 * RakNet might decide not to delete right now the packet in order to use it later. 
	 * @param packet the packet to deallocate. 
	 */
	virtual void DeallocatePacket( Packet *packet ) = 0;

	/**
	 * Returns true if the client is connected to a responsive server
	 * @return true if connected to a server 
	 */
	virtual bool IsConnected( void ) const = 0;

	/**
	 * Return the player number of the server.
	 * @return the server playerID
	 */
	virtual PlayerID GetServerID( void ) const = 0;

	/**
	 * Return the player number the server has assigned to you.
	 *
	 * @return our player ID
	 * @note that unlike in previous versions, this is a struct and is not sequential
	 *
	 */
	virtual PlayerID GetPlayerID( void ) const = 0;
};

#endif
