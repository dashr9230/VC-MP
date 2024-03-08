// This file is part of RakNet Copyright 2003, 2004 Rakkarsoft LLC and Kevin Jenkins.

// Usage of Raknet is subject to the appropriate licence agreement.
// "Shareware" Licensees with Rakkarsoft LLC are subject to the shareware license found at http://www.rakkarsoft.com/shareWareLicense.html which you agreed to upon purchase of a "Shareware license"
// "Commercial" Licensees with Rakkarsoft LLC are subject to the commercial license found at http://www.rakkarsoft.com/sourceCodeLicense.html which you agreed to upon purchase of a "Commercial license"
// All other users are subject to the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

// Refer to the appropriate license agreement for distribution, modification, and warranty rights.

#ifndef __RAK_SERVER_INTERFACE_H
#define __RAK_SERVER_INTERFACE_H

#include "NetworkTypes.h"
#include "PacketPriority.h"
#include "BitStream.h"

class RakServerInterface
{
public:

	// Call this to initiate the server with the number of players you want to be allowed connected at once
	// Current maximum number of allowed players is 65535
	// connectionValidationInteger is for legacy purposes and is unused
	// _threadSleepTimer: <0 for single threaded, >=0 for how many ms to Sleep each internal update cycle (recommended 30 for low performance, 0 for regular, -1 for high)
	// Port is the port you want the server to read and write on
	// Make sure this port is open for UDP
	// Returns true on successful initiation, false otherwise
	virtual bool Start(unsigned short AllowedPlayers, unsigned long connectionValidationInteger, int threadSleepTimer, unsigned short port)=0;

	// Description:
	// Must be called while offline
	// Secures connections though a combination of SHA1, AES128, SYN Cookies, and RSA to prevent
	// connection spoofing, replay attacks, data eavesdropping, packet tampering, and MitM attacks.
	// There is a significant amount of processing and a slight amount of bandwidth
	// overhead for this feature.
	//
	// If you accept connections, you must call this or else secure connections will not be enabled
	// for incoming connections.
	//
	// Parameters:
	// RSAp, RSAq - A pointer to the private keys from the RSACrypt class.  See the Encryption sample
	// If the private keys are 0, then a new key will be generated when this function is called
	virtual void InitializeSecurity(char *RSAp, char *RSAq)=0;

	// Set the password clients have to use to connect to this server.  The password persists between connections.
	// Pass 0 for no password.
	// You can call this anytime
	virtual void SetPassword(char *_password)=0;

	// This function only works while the server is active (Use the Start function).  Returns false on failure, true on success
	// Send the bitstream to whichever playerId you specify.
	// You can set the first byte to a packet identifier, however you will need to have TYPE_CHECKING undefined or the internal type checking
	// will add extra data and make this not work.  If you want TYPE_CHECKING on, you will need to use BitStream::WriteBits to avoid the type checking.
	// This interface will probably change to fix this in future versions.
	// If you aren't sure what to specify for priority and reliability, use HIGH_PRIORITY and RELIABLE, 0 for ordering stream
	// Set broadcast to true to broadcast to all connected clients EXCEPT the one specified in the playerId field.
	// To broadcast to everyone specify UNASSIGNED_PLAYER_ID for the playerId field.
	virtual bool Send(RakNet::BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingStream, PlayerID playerId, bool broadcast)=0;

	// Ping all players every so often.  This is on by default.  In games where you don't care about ping you can call
	// StopOccasionalPing to save the bandwidth
	// This will work anytime
	virtual void StartOccasionalPing(void)=0;

	// Start or restart the synchronized random integer.  This is on by default.  Call StopSynchronizedRandomInteger
	// to stop it keeping the number in synch
	virtual void StartSynchronizedRandomInteger(void)=0;

	// Register a C function as available for calling as a remote procedure call
	// uniqueID should be a null terminated non-case senstive string of only letters to identify this procedure
	// Parameter 2 should be the name of the C function or C++ singleton to be used as a function pointer
	// This can be called whether the client is active or not, and registered functions stay registered unless unregistered with
	// UnregisterAsRemoteProcedureCall
	virtual void RegisterAsRemoteProcedureCall(char* uniqueID, void (*functionName)(char *input, int numberOfBitsOfData, PlayerID sender))=0;

	// Calls a C function on the client that the client already registered using RegisterAsRemoteProcedureCall
	// Pass the data you want to pass to that function in parameters, or 0 for no data to pass
	// You can also pass a regular data stream which will be converted to a bitstream internally by passing data and bit length
	// playerId and broadcast are used the same way as in Send to specify a recipient or to broadcast to all clients
	// If you want that function to return data you should call RPC from that system in the same way
	// Returns true on a successful packet send (this does not indicate the recipient performed the call), false on failure
	// The uniqueID must be composed of a string with only characters from a-z and is not case sensitive
	virtual bool RPC(char* uniqueID, RakNet::BitStream *parameters, PacketPriority priority, PacketReliability reliability, char orderingStream, PlayerID playerId, bool broadcast, bool shiftTimestamp)=0;

	// This function is only useful for looping through all players.
	// Index should range between 0 and the maximum number of players allowed - 1.
	virtual PlayerID GetPlayerIDFromIndex(int index)=0;

	// Description:
	// Bans an IP from connecting.  Banned IPs persist between connections.
	//
	// Parameters
	// IP - Dotted IP address.  Can use * as a wildcard, such as 128.0.0.* will ban
	// All IP addresses starting with 128.0.0
	virtual void AddToBanList(const char *IP)=0;
};

#endif
