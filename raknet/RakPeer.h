// This file is part of RakNet Copyright 2003, 2004 Rakkarsoft LLC and Kevin Jenkins.

// Usage of Raknet is subject to the appropriate licence agreement.
// "Shareware" Licensees with Rakkarsoft LLC are subject to the shareware license found at http://www.rakkarsoft.com/shareWareLicense.html which you agreed to upon purchase of a "Shareware license"
// "Commercial" Licensees with Rakkarsoft LLC are subject to the commercial license found at http://www.rakkarsoft.com/sourceCodeLicense.html which you agreed to upon purchase of a "Commercial license"
// All other users are subject to the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

// Refer to the appropriate license agreement for distribution, modification, and warranty rights.

#ifndef __RAK_PEER_H
#define __RAK_PEER_H

#include "ReliabilityLayer.h"
#include "RakPeerInterface.h"
#include "RSACrypt.h"

class RakPeer : public RakPeerInterface
{
public:
	// Constructor
	RakPeer();

	/**
	* Must be called while offline
	* Secures connections though a combination of SHA1, AES128, SYN Cookies, and RSA to prevent
	* connection spoofing, replay attacks, data eavesdropping, packet tampering, and MitM attacks.
	* There is a significant amount of processing and a slight amount of bandwidth
	* overhead for this feature.
	*
	* If you accept connections, you must call this or else secure connections will not be enabled
	* for incoming connections.
	* If you are connecting to another system, you can call this with values for the
	* (e and p,q) public keys before connecting to prevent MitM
	*
	* @param pubKeyE A pointer to the public keys from the RSACrypt class.  
	* @param pubKeyN A pointer to the public keys from the RSACrypt class. 
	* @param privKeyP Public key generated from the RSACrypt class.  
	* @param privKeyQ Public key generated from the RSACrypt class.  
	* If the private keys are 0, then a new key will be generated when this function is called
	* 
	* @see the Encryption sample
	*/
	void InitializeSecurity(const char *pubKeyE, const char *pubKeyN, const char *privKeyP, const char *privKeyQ );

protected:

	bool endThreads;
	char field_5;
	char field_6;
	short field_7;
	short field_9;
	RakNet::BitStream field_B;
	RakNet::BitStream field_1C;
	RakNet::BitStream field_2D;
	RakNet::BitStream field_3E;
	PlayerID myPlayerId;
	int field_55;

	enum
	{
		_UNK_MUTEX_0,
		_UNK_MUTEX_1,
		_UNK_MUTEX_2,
		_UNK_MUTEX_3,
		_UNK_MUTEX_4,
		NUMBER_OF_RAKPEER_MUTEXES
	};
	SimpleMutex rakPeerMutexes[ NUMBER_OF_RAKPEER_MUTEXES ];

	char _gapD1;

	struct RequestedConnectionStruct
	{
		// TODO: RequestedConnectionStruct
		char _gap0;
	};

	// The list of people we have tried to connect to recently
	BasicDataStructures::Queue<RequestedConnectionStruct> requestedConnectionsList;

	int field_E2;
	int field_E6;

	SimpleMutex field_F6;
	SimpleMutex field_10E;

	BasicDataStructures::Queue<Packet *> incomingPacketQueue;

	BasicDataStructures::List<char*> field_136;

	// Compression stuff
	unsigned long frequencyTable[256];

	void GenerateSYNCookieRandomNumber( void );

	int field_542;
	int field_546;
	int field_54A;
	int field_54E;
	int field_552;
	int field_556;

	int MTUSize;
	char field_56E;

	SOCKET connectionSocket;
	big::RSACrypt<RSA_BIT_SIZE> rsacrypt;

	bool keysLocallyGenerated, usingSecurity;
	unsigned int randomNumberExpirationTime;
	unsigned char newRandomNumber[ 20 ], oldRandomNumber[ 20 ];

	char field_6FE;
};

#endif
