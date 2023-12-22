
#if defined(_MSC_VER) && _MSC_VER < 1299 // VC6 doesn't support template specialization
#include "BitStream_NoTemplate.cpp"
#else

#include "BitStream.h"

using namespace RakNet;

BitStream::BitStream()
{
	numberOfBitsUsed = 0;
	//numberOfBitsAllocated = 32 * 8;
	numberOfBitsAllocated = BITSTREAM_STACK_ALLOCATION_SIZE * 8;
	readOffset = 0;
	//data = ( unsigned char* ) malloc( 32 );
	data = ( unsigned char* ) stackData;

#ifdef _DEBUG	
//	assert( data );
#endif
	//memset(data, 0, 32);
	copyData = true;
}

#endif // #if _MSC_VER < 1299 
