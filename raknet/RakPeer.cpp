
#include "RakPeer.h"

#include "GetTime.h"
#include "Rand.h"

static const unsigned int SYN_COOKIE_OLD_RANDOM_NUMBER_DURATION = 5000;

RakPeer::RakPeer()
{
	memset(frequencyTable, 0, sizeof(unsigned long) * 256);
	connectionSocket=INVALID_SOCKET;
	MTUSize=DEFAULT_MTU_SIZE;
	field_9=0;
	field_7=0;
	endThreads=true;
	field_5=0;
	field_6=0;
	connectionSocket=INVALID_SOCKET;
	myPlayerId=UNASSIGNED_PLAYER_ID;

	// TODO: RakPeer::RakPeer()
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
// Must be called while offline
// Secures connections though a combination of SHA1, AES128, SYN Cookies, and RSA to prevent
// connection spoofing, replay attacks, data eavesdropping, packet tampering, and MitM attacks.
// There is a significant amount of processing and a slight amount of bandwidth
// overhead for this feature.
//
// If you accept connections, you must call this or else secure connections will not be enabled
// for incoming connections.
// If you are connecting to another system, you can call this with values for the
// (e and p,q) public keys before connecting to prevent MitM
//
// Parameters:
// pubKeyE, pubKeyN - A pointer to the public keys from the RSACrypt class. See the Encryption sample
// privKeyP, privKeyQ - Private keys generated from the RSACrypt class.  See the Encryption sample
// If the private keys are 0, then a new key will be generated when this function is called
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void RakPeer::InitializeSecurity(const char *pubKeyE, const char *pubKeyN, const char *privKeyP, const char *privKeyQ )
{
	if ( endThreads == false )
		return ;

	// Setting the client key is e,n,
	// Setting the server key is p,q
	if ( ( privKeyP && privKeyQ && ( pubKeyE || pubKeyN ) ) ||
		( pubKeyE && pubKeyN && ( privKeyP || privKeyQ ) ) ||
		( privKeyP && privKeyQ == 0 ) ||
		( privKeyQ && privKeyP == 0 ) ||
		( pubKeyE && pubKeyN == 0 ) ||
		( pubKeyN && pubKeyE == 0 ) )
	{
		// Invalid parameters
		assert( 0 );
	}

	seedMT( RakNet::GetTime() );

	GenerateSYNCookieRandomNumber();

	usingSecurity = true;


	// TODO: RakPeer::InitializeSecurity
}


// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void RakPeer::GenerateSYNCookieRandomNumber( void )
{
	unsigned int number;
	int i;
	memcpy( oldRandomNumber, newRandomNumber, sizeof( newRandomNumber ) );

	for ( i = 0; i < sizeof( newRandomNumber ); i += sizeof( number ) )
	{
		number = randomMT();
		memcpy( newRandomNumber + i, ( char* ) & number, sizeof( number ) );
	}

	randomNumberExpirationTime = RakNet::GetTime() + SYN_COOKIE_OLD_RANDOM_NUMBER_DURATION;
}
