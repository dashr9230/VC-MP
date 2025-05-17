/* -*- mode: c++; c-file-style: raknet; tab-always-indent: nil; -*- */
/**
 * @file 
 * @brief Client communication End Point Implementation
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
#include "RakClient.h"

bool RakClient::Connect( char* host, unsigned short serverPort, unsigned short clientPort, unsigned int connectionValidationInteger, int threadSleepTimer )
{
	// TODO: RakClient::Connect
	return false;
}

void RakClient::Disconnect( unsigned int blockDuration )
{
	// TODO: RakClient::Disconnect
}

void RakClient::SetPassword( char *_password )
{
	// TODO: RakClient::SetPassword
}

bool RakClient::Send( RakNet::BitStream * bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel )
{
	// TODO: RakClient::Send
	return false;
}

Packet* RakClient::Receive( void )
{
	// TODO: RakClient::Receive
	return 0;
}

void RakClient::DeallocatePacket( Packet *packet )
{
	// TODO: RakClient::DeallocatePacket
}

bool RakClient::IsConnected( void ) const
{
	unsigned short numberOfSystems;

	RakPeer::GetConnectionList( 0, &numberOfSystems );
	return numberOfSystems == 1;
}

PlayerID RakClient::GetServerID( void ) const
{
	// TODO: RakClient::GetServerID
	return UNASSIGNED_PLAYER_ID;
}

PlayerID RakClient::GetPlayerID( void ) const
{
	// TODO: RakClient::GetPlayerID
	return UNASSIGNED_PLAYER_ID;
}