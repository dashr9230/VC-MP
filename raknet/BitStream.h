
#if defined(_MSC_VER) && _MSC_VER < 1299 // VC6 doesn't support template specialization
#include "BitStream_NoTemplate.h"
#else

#ifndef __BITSTREAM_H
#define __BITSTREAM_H

#include "Export.h"

#define BITSTREAM_STACK_ALLOCATION_SIZE 256

namespace RakNet
{
	class RAK_DLL_EXPORT BitStream
	{

	public:
		/// Default Constructor 
		BitStream();

	private:

		int numberOfBitsUsed;

		int numberOfBitsAllocated;

		int readOffset;

		unsigned char *data;

		/// true if the internal buffer is copy of the data passed to the constructor
		bool copyData;

		/// BitStreams that use less than BITSTREAM_STACK_ALLOCATION_SIZE use the stack, rather than the heap to store data.  It switches over if BITSTREAM_STACK_ALLOCATION_SIZE is exceeded
		unsigned char stackData[BITSTREAM_STACK_ALLOCATION_SIZE];
	};


}

#endif

#endif // VC6
