// This file is part of RakNet Copyright 2003, 2004 Rakkarsoft LLC and Kevin Jenkins.

// Usage of Raknet is subject to the appropriate licence agreement.
// "Shareware" Licensees with Rakkarsoft LLC are subject to the shareware license found at http://www.rakkarsoft.com/shareWareLicense.html which you agreed to upon purchase of a "Shareware license"
// "Commercial" Licensees with Rakkarsoft LLC are subject to the commercial license found at http://www.rakkarsoft.com/sourceCodeLicense.html which you agreed to upon purchase of a "Commercial license"
// All other users are subject to the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

// Refer to the appropriate license agreement for distribution, modification, and warranty rights.

#ifndef __NETWORK_TYPES_H
#define __NETWORK_TYPES_H

struct PlayerID
{
	unsigned long binaryAddress; // From inet_addr
	unsigned short port;
};

struct Packet
{
	char _gap0[8];
	unsigned long length;
	char _gapC[4];
	char* data;
};

//-----------------------------------------------------
// RPC FUNCTION IMPLEMENTATION
// --------------------------------------------------------
//
// Use the following C function prototype for your callbacks
// void functionName(char *input, int numberOfBitsOfData, PlayerID sender);
//
// If you pass input data, you can parse the input data in two ways.
//
// 1.
// Cast input to a struct (such as if you sent a struct)
// i.e. MyStruct *s = (MyStruct*) input;
// Make sure that the sizeof(MyStruct) is equal to the number of bytes passed!
//
// 2.
// Create a BitStream instance with input as data and the number of bytes
// i.e. BitStream myBitStream(input, (numberOfBitsOfData-1)/8+1)
//
// (numberOfBitsOfData-1)/8+1 is how convert from bits to bytes
//
// Full example:
//
// void MyFunc(char *input, int numberOfBitsOfData, PlayerID sender) {}
// RakClient *rakClient;
// REGISTER_AS_REMOTE_PROCEDURE_CALL(rakClient, MyFunc);
// This would allow MyFunc to be called from the server using  (for example)
// rakServer->RPC("MyFunc", 0, clientID, false);

#define REGISTER_AS_REMOTE_PROCEDURE_CALL(networkObject, functionName) (networkObject)->RegisterAsRemoteProcedureCall((#functionName),(functionName))

#endif
