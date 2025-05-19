/* -*- mode: c++; c-file-style: raknet; tab-always-indent: nil; -*- */
/**
 * @ingroup RAKNET_RPC 
 * @file 
 * @brief Internal Stuff for RPC Handling  
 *
 * This file is part of RakNet Copyright 2003, 2004
 * Rakkarsoft LLC and Kevin Jenkins.
 *
 * Usage of Raknet is subject to the appropriate licence agreement.
 * "Shareware" Licensees with Rakkarsoft LLC are subject to the
 * shareware license found at
 * http://www.rakkarsoft.com/shareWareLicense.html which you agreed to
 * upon purchase of a "Shareware license" "Commercial" Licensees with
 * Rakkarsoft LLC are subject to the commercial license found at
 * http://www.rakkarsoft.com/sourceCodeLicense.html which you agreed
 * to upon purchase of a "Commercial license" All other users are
 * subject to the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * Refer to the appropriate license agreement for distribution,
 * modification, and warranty rights.
 */
#include "RPCNode.h"
#include <assert.h>
#include <string.h>

RPCNode::RPCNode()
{
	uniqueIdentifier = 0;
	functionName = 0;
}

RPCNode::RPCNode( char* uniqueID, void ( *_functionName ) ( char *input, int numberOfBitsOfData, PlayerID sender ) )
{
#ifdef _DEBUG
	assert( uniqueID );
	assert( uniqueID[ 0 ] );
#endif

	uniqueIdentifier = new char [ strlen( uniqueID ) + 1 ];
	strcpy( uniqueIdentifier, uniqueID );
	functionName = _functionName;
}

RPCNode::RPCNode( const RPCNode& input )
{
	if ( input.uniqueIdentifier != 0 )
	{
		uniqueIdentifier = new char [ strlen( input.uniqueIdentifier ) + 1 ];
		strcpy( uniqueIdentifier, input.uniqueIdentifier );
	}

	else
	{
		uniqueIdentifier = 0;
	}

	functionName = input.functionName;
}

RPCNode& RPCNode::operator = ( const RPCNode& input )
{
	if ( &input == this )
		return * this;

	if ( input.uniqueIdentifier != 0 )
	{
		if ( uniqueIdentifier != 0 )
			delete [] uniqueIdentifier;
			
		uniqueIdentifier = new char [ strlen( input.uniqueIdentifier ) + 1 ];
		
		strcpy( uniqueIdentifier, input.uniqueIdentifier );
	}

	else
	{
		delete uniqueIdentifier;
		uniqueIdentifier = 0;
	}

	functionName = input.functionName;

	return *this;
}

RPCNode::~RPCNode()
{
	delete [] uniqueIdentifier;
}

int operator==( const RPCNode& left, const RPCNode& right )
{
	if ( strcmp( left.uniqueIdentifier, right.uniqueIdentifier ) == 0 )
		return !0;

	return 0;
}

int operator>( const RPCNode& left, const RPCNode& right )
{
	if ( strcmp( left.uniqueIdentifier, right.uniqueIdentifier ) > 0 )
		return !0;

	return 0;
}

int operator<( const RPCNode& left, const RPCNode& right )
{
	if ( strcmp( left.uniqueIdentifier, right.uniqueIdentifier ) < 0 )
		return !0;

	return 0;
}

