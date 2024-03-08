// This file is part of RakNet Copyright 2003, 2004 Rakkarsoft LLC and Kevin Jenkins.

// Usage of Raknet is subject to the appropriate licence agreement.
// "Shareware" Licensees with Rakkarsoft LLC are subject to the shareware license found at http://www.rakkarsoft.com/shareWareLicense.html which you agreed to upon purchase of a "Shareware license"
// "Commercial" Licensees with Rakkarsoft LLC are subject to the commercial license found at http://www.rakkarsoft.com/sourceCodeLicense.html which you agreed to upon purchase of a "Commercial license"
// All other users are subject to the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

// Refer to the appropriate license agreement for distribution, modification, and warranty rights.

#ifndef __BITSTREAM_H
#define __BITSTREAM_H

namespace RakNet
{

#define BITS_TO_BYTES(x) (((x)+7)>>3)

class BitStream
{
public:
	BitStream();
	~BitStream();

	// Write the native types to the end of the buffer
	void Write(unsigned char input);
	void Write(unsigned int input);
	void Write(unsigned long input);
	void Write(char* input, int numberOfBytes); // Write an array or casted stream

	// Write numberToWrite bits from the input source
	// Right aligned data means in the case of a partial byte, the bits are aligned from the right (bit 0) rather than the left (as in the normal internal representation)
	// You would set this to true when writing user data, and false when writing the contents of a bitstream for a later read
	void WriteBits(unsigned char* input, int numberOfBitsToWrite, bool rightAlignedBits=true);

private:

	void AddBitsAndReallocate(int numberOfBitsToWrite);  // Reallocates (if necessary) in preparation of writing numberOfBitsToWrite

	int numberOfBitsUsed, numberOfBitsAllocated, readOffset;
	unsigned char *data;
	bool copyData;
};
}

#endif
