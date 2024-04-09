
#ifndef __RAK_CLIENT_H
#define __RAK_CLIENT_H

#include "RakPeer.h"
#include "RakClientInterface.h"

class RakClient : public RakPeer, public RakClientInterface
{
public:
	// Constructor
	RakClient();

	/**
	 * Can be called to use specific public RSA keys. (e and n)
	 * In order to prevent altered keys.  Will return ID_RSA_PUBLIC_KEY_MISMATCH in a packet
	 * If a key has been altered.
	 *
	 * @param privKeyP Private keys generated from the RSACrypt class. Can be 0
	 * @param privKeyQ Private keys generated from the RSACrypt class. Can be 0 
	 * @see   Encryption sample. 
	 */
	void InitializeSecurity( const char *privKeyP, const char *privKeyQ );

private:

	RakNet::BitStream field_703;

	struct OtherClientsStruct
	{
		char _gap0[8];
		RakNet::BitStream staticData;
		bool isActive;
	} otherClients[32];

	int field_A5C;
};

#endif
