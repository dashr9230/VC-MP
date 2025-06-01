/* -*- mode: c++; c-file-style: raknet; tab-always-indent: nil; -*- */
/**
 * @file
 * @brief Unique Player Identifier Class implementation
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
#include "NetworkTypes.h"
#include <stdio.h>
#include <string.h>

#if defined(_WIN32)
// IP_DONTFRAGMENT is different between winsock 1 and winsock 2.  Therefore, Winsock2.h must be linked againt Ws2_32.lib
// winsock.h must be linked against WSock32.lib.  If these two are mixed up the flag won't work correctly
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include "Itoa.h"

int operator==( const PlayerID& left, const PlayerID& right )
{
	return left.binaryAddress == right.binaryAddress && left.port == right.port;
}

int operator!=( const PlayerID& left, const PlayerID& right )
{
	return left.binaryAddress != right.binaryAddress || left.port != right.port;
}

int operator>( const PlayerID& left, const PlayerID& right )
{
	return ( ( left.binaryAddress > right.binaryAddress ) || ( ( left.binaryAddress == right.binaryAddress ) && ( left.port > right.port ) ) );
}

int operator<( const PlayerID& left, const PlayerID& right )
{
	return ( ( left.binaryAddress < right.binaryAddress ) || ( ( left.binaryAddress == right.binaryAddress ) && ( left.port < right.port ) ) );
}

const char *PlayerID::ToString(bool writePort) const
{
	static unsigned char strIndex=0;
	static char str[8][22];

	unsigned char lastStrIndex=strIndex;
	strIndex++;
	ToString(writePort, str[lastStrIndex&7]);
	return (char*) str[lastStrIndex&7];
}

void PlayerID::ToString(bool writePort, char *dest) const
{
	if (*this==UNASSIGNED_PLAYER_ID)
	{
		strcpy(dest, "UNASSIGNED_PLAYER_ID");
		return;
	}

#if defined(_XBOX) || defined(X360)
	Itoa(binaryAddress, dest, 10);
	strcat(dest, ":");
	Itoa(port, dest+strlen(dest), 10);
#else
	in_addr in;
	in.s_addr = binaryAddress;
	strcpy(dest, inet_ntoa( in ));
	if (writePort)
	{
		strcat(dest, ":");
		Itoa(port, dest+strlen(dest), 10);
	}
#endif

}
