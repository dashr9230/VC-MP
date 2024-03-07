// This file is part of RakNet Copyright 2003, 2004 Rakkarsoft LLC and Kevin Jenkins.

// Usage of Raknet is subject to the appropriate licence agreement.
// "Shareware" Licensees with Rakkarsoft LLC are subject to the shareware license found at http://www.rakkarsoft.com/shareWareLicense.html which you agreed to upon purchase of a "Shareware license"
// "Commercial" Licensees with Rakkarsoft LLC are subject to the commercial license found at http://www.rakkarsoft.com/sourceCodeLicense.html which you agreed to upon purchase of a "Commercial license"
// All other users are subject to the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

// Refer to the appropriate license agreement for distribution, modification, and warranty rights.

#ifndef __RAK_SERVER_H
#define __RAK_SERVER_H

#include "RakPeer.h"
#include "RakServerInterface.h"

class RakServer : public RakServerInterface, public RakPeer
{
public:

	// Call this to initiate the server with the number of players you want to be allowed connected at once
	// Current maximum number of allowed players is 65535
	// connectionValidationInteger is for legacy purposes and is unused
	// _threadSleepTimer: <0 for don't sleep, >=0 for how many ms to Sleep each internal update cycle (recommended you start with 15, try different values)
	// Port is the port you want the server to read and write on
	// Make sure this port is open for UDP
	// Returns true on successful initiation, false otherwise
	bool Start(unsigned short AllowedPlayers, unsigned long connectionValidationInteger, int threadSleepTimer, unsigned short port);

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
	void InitializeSecurity(char *RSAp, char *RSAq);

	// Set the password clients have to use to connect to this server.  The password persists between connections.
	// Pass 0 for no password.
	// You can call this anytime
	void SetPassword(char *_password);

	// Ping all players every so often.  This is on by default.  In games where you don't care about ping you can call
	// StopOccasionalPing to save the bandwidth
	// This will work anytime
	void StartOccasionalPing(void);

	// Start or restart the synchronized random integer.  This is on by default.  Call StopSynchronizedRandomInteger
	// to stop it keeping the number in synch
	void StartSynchronizedRandomInteger(void);

	// Register a C function as available for calling as a remote procedure call
	// uniqueID should be a null terminated non-case senstive string of only letters to identify this procedure
	// Parameter 2 should be the name of the C function or C++ singleton to be used as a function pointer
	// This can be called whether the client is active or not, and registered functions stay registered unless unregistered with
	// UnregisterAsRemoteProcedureCall
	void RegisterAsRemoteProcedureCall(char* uniqueID, void (*functionName)(char *input, int numberOfBitsOfData, PlayerID sender));

	// Description:
	// Bans an IP from connecting.  Banned IPs persist between connections.
	//
	// Parameters
	// IP - Dotted IP address.  Can use * as a wildcard, such as 128.0.0.* will ban
	// All IP addresses starting with 128.0.0
	void AddToBanList(const char *IP);

private:
};

#endif
