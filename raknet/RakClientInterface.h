
#ifndef __RAK_CLIENT_INTERFACE_H
#define __RAK_CLIENT_INTERFACE_H

class RakClientInterface
{
public:

	/**
	* Can be called to use specific public RSA keys. (e and n)
	* In order to prevent altered keys.  Will return ID_RSA_PUBLIC_KEY_MISMATCH in a packet
	* If a key has been altered.
	*
	* @param privKeyP Private keys generated from the RSACrypt class. Can be 0
	* @param privKeyQ Private keys generated from the RSACrypt class. Can be 0 
	* @see   Encryption sample. 
	*/
	virtual void InitializeSecurity( const char *privKeyP, const char *privKeyQ ) = 0;

};

#endif
