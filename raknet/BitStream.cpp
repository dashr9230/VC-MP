// This file is part of RakNet Copyright 2003, 2004 Rakkarsoft LLC and Kevin Jenkins.

// Usage of Raknet is subject to the appropriate licence agreement.
// "Shareware" Licensees with Rakkarsoft LLC are subject to the shareware license found at http://www.rakkarsoft.com/shareWareLicense.html which you agreed to upon purchase of a "Shareware license"
// "Commercial" Licensees with Rakkarsoft LLC are subject to the commercial license found at http://www.rakkarsoft.com/sourceCodeLicense.html which you agreed to upon purchase of a "Commercial license"
// All other users are subject to the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

// Refer to the appropriate license agreement for distribution, modification, and warranty rights.

#include "BitStream.h"
#include <malloc.h>
#include <assert.h>

using namespace RakNet;

BitStream::BitStream()
{
	numberOfBitsUsed=0;
	numberOfBitsAllocated=32 * 8;
	readOffset=0;
	data=(unsigned char*)malloc(32);
#ifdef _DEBUG
	assert(data);
#endif
	//memset(data, 0, 32);
	copyData=true;
}

BitStream::~BitStream()
{
	if (copyData)
		free(data);  // Use realloc and free so we are more efficient than delete and new for resizing
}

void BitStream::Write(unsigned char input)
{
#ifdef TYPE_CHECKING
	unsigned char ID = 1;
	WriteBits((unsigned char*)&ID, sizeof(unsigned char)*8, true);
#endif

	WriteBits((unsigned char*)&input, sizeof(input)*8, true);
}

void BitStream::Write(unsigned int input)
{
#ifdef TYPE_CHECKING
	unsigned char ID = 5;
	WriteBits((unsigned char*)&ID, sizeof(unsigned char)*8, true);
#endif
	WriteBits((unsigned char*)&input, sizeof(input)*8, true);
}

void BitStream::Write(unsigned long input)
{
#ifdef TYPE_CHECKING
	unsigned char ID = 7;
	WriteBits((unsigned char*)&ID, sizeof(unsigned char)*8, true);
#endif
	WriteBits((unsigned char*)&input, sizeof(input)*8, true);
}

// Write an array or casted stream
void BitStream::Write(char* input, int numberOfBytes)
{
#ifdef TYPE_CHECKING
	unsigned char ID =11;
	WriteBits((unsigned char*)&ID, sizeof(unsigned char)*8, true);
	WriteBits((unsigned char*)&numberOfBytes, sizeof(int)*8, true);
#endif

	WriteBits((unsigned char*)input, numberOfBytes*8, true);
}

// Write numberToWrite bits from the input source
void  BitStream::WriteBits(unsigned char *input, int numberOfBitsToWrite, bool rightAlignedBits)
{
	//if (numberOfBitsToWrite<=0)
		//return;

	AddBitsAndReallocate(numberOfBitsToWrite);
	int offset=0;
	unsigned char dataByte;
	int numberOfBitsUsedMod8;

	numberOfBitsUsedMod8=numberOfBitsUsed%8;

	// Faster to put the while at the top surprisingly enough
	while(numberOfBitsToWrite>0)
	//do
	{
		dataByte = *(input+offset);
		if (numberOfBitsToWrite<8 && rightAlignedBits) // rightAlignedBits means in the case of a partial byte, the bits are aligned from the right (bit 0) rather than the left (as in the normal internal representation)
			dataByte<<=8-numberOfBitsToWrite;	 // shift left to get the bits on the left, as in our internal representation

		// Copy over the new data.
		*(data+(numberOfBitsUsed>>3)) |= dataByte >> (numberOfBitsUsedMod8); // First half
		if (8 - (numberOfBitsUsedMod8) < 8 && 8 - (numberOfBitsUsedMod8) < numberOfBitsToWrite) // If we didn't write it all out in the first half (8 - (numberOfBitsUsed%8) is the number we wrote in the first half)
			*(data+(numberOfBitsUsed>>3) + 1) |= (unsigned char)(dataByte << (8 - (numberOfBitsUsedMod8))); // Second half (overlaps byte boundary)

		if (numberOfBitsToWrite>=8)
			numberOfBitsUsed+= 8;
		else
		{
			numberOfBitsUsed+= numberOfBitsToWrite;
		}
		numberOfBitsToWrite-= 8;

		offset++;
	}
//	} while(numberOfBitsToWrite>0);

}

// Reallocates (if necessary) in preparation of writing numberOfBitsToWrite
void  BitStream::AddBitsAndReallocate(int numberOfBitsToWrite)
{
	if (numberOfBitsToWrite<=0)
		return;

	int newNumberOfBitsAllocated = numberOfBitsToWrite + numberOfBitsUsed;
	if ( numberOfBitsToWrite + numberOfBitsUsed>0 && ((numberOfBitsAllocated-1)>>3) < ((newNumberOfBitsAllocated-1)>>3)) // If we need to allocate 1 or more new bytes
	{
		#ifdef _DEBUG
		// If this assert hits then we need to specify true for the third parameter in the constructor
		// It needs to reallocate to hold all the data and can't do it unless we allocated to begin with
		assert(copyData==true);
		#endif

		// Less memory efficient but saves on news and deletes
		newNumberOfBitsAllocated=(numberOfBitsToWrite + numberOfBitsUsed) * 2;
		int newByteOffset = BITS_TO_BYTES(numberOfBitsAllocated);
		// Use realloc and free so we are more efficient than delete and new for resizing
		data = (unsigned char*) realloc(data, BITS_TO_BYTES(newNumberOfBitsAllocated));
		#ifdef _DEBUG
		assert(data); // Make sure realloc succeeded
		#endif
		//memset(data+newByteOffset, 0,  ((newNumberOfBitsAllocated-1)>>3) - ((numberOfBitsAllocated-1)>>3)); // Set the new data block to 0
	}

	if (newNumberOfBitsAllocated > numberOfBitsAllocated)
		numberOfBitsAllocated=newNumberOfBitsAllocated;
}
