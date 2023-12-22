
#ifndef __RAK_PEER_H
#define __RAK_PEER_H

#include "Export.h"
#include "RakPeerInterface.h"
#include "BitStream.h"
#include "SimpleMutex.h"

class RAK_DLL_EXPORT RakPeer : public RakPeerInterface
{
public:

protected:

	char _gap4[8];
	RakNet::BitStream field_C;
	char _gap11D[3];
	RakNet::BitStream field_120;

	enum
	{
		Unnamed_Mutex,
		NUMBER_OF_RAKPEER_MUTEXES
	};
	SimpleMutex rakPeerMutexes[ NUMBER_OF_RAKPEER_MUTEXES ];

	SimpleMutex field_37C;
	SimpleMutex field_394;

	unsigned int field_3DC[256];
};

#endif
