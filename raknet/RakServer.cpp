// This file is part of RakNet Copyright 2003, 2004 Rakkarsoft LLC and Kevin Jenkins.

// Usage of Raknet is subject to the appropriate licence agreement.
// "Shareware" Licensees with Rakkarsoft LLC are subject to the shareware license found at http://www.rakkarsoft.com/shareWareLicense.html which you agreed to upon purchase of a "Shareware license"
// "Commercial" Licensees with Rakkarsoft LLC are subject to the commercial license found at http://www.rakkarsoft.com/sourceCodeLicense.html which you agreed to upon purchase of a "Commercial license"
// All other users are subject to the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

// Refer to the appropriate license agreement for distribution, modification, and warranty rights.

#include "RakServer.h"

bool RakServer::Start(unsigned short AllowedPlayers, unsigned long connectionValidationInteger, int threadSleepTimer, unsigned short port)
{
	// TODO: RakServer::Start
	return false;
}

void RakServer::InitializeSecurity(char *RSAp, char *RSAq)
{
	// TODO: RakServer::InitializeSecurity
}

void RakServer::SetPassword(char *_password)
{
	// TODO: RakServer::SetPassword
}

bool RakServer::Send(RakNet::BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingStream, PlayerID playerId, bool broadcast)
{
	// TODO: RakServer::Send
	return false;
}

void RakServer::StartOccasionalPing(void)
{
	// TODO: RakServer::StartOccasionalPing
}

void RakServer::StartSynchronizedRandomInteger(void)
{
	// TODO: RakServer::StartSynchronizedRandomInteger
}

void RakServer::RegisterAsRemoteProcedureCall(char* uniqueID, void (*functionName)(char *input, int numberOfBitsOfData, PlayerID sender))
{
	// TODO: RakServer::RegisterAsRemoteProcedureCall
}

bool RakServer::RPC(char* uniqueID, RakNet::BitStream *parameters, PacketPriority priority, PacketReliability reliability, char orderingStream, PlayerID playerId, bool broadcast, bool shiftTimestamp)
{
	// TODO: RakServer::RPC
	return false;
}

PlayerID RakServer::GetPlayerIDFromIndex(int index)
{
	// TODO: RakServer::GetPlayerIDFromIndex
	return UNASSIGNED_PLAYER_ID;
}

void RakServer::AddToBanList(const char *IP)
{
	// TODO: RakServer::AddToBanList
}
