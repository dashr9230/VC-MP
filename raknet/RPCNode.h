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
#ifndef __RPC_NODE
#define __RPC_NODE

#include "NetworkTypes.h"

/**
 * @defgroup RAKNET_RPC Remote Procedure Call Subsystem
 * @brief Remote Function Invocation
 *
 * The Remote Procedure Call Subsystem provide ability to call
 * function on a remote host knowing its name and its parameters.
 *
 * @todo Add here an example on how to register and use an RPC.
 *
 */

// RPC stuff.  Ignore this

/**
 * @ingroup RAKNET_RPC
 * @note You should not use this class directly. It is used internaly in the
 * RPC Subsystem
 *
 * @brief Map registered procedure inside of a peer.
 *
 * An RPC Node corresponds to one register function.
 */

struct RPCNode
{
	/**
	 * A unique identifier
	 */
	char *uniqueIdentifier;
	/**
	 * A pointer to the function to be called
	 */
	void ( *functionName ) ( char *input, int numberOfBitsOfData, PlayerID sender );

	/**
	 * Constructor
	 * @param uniqueID the id of the function
	 * @param _functionName a pointer to a function C function or static class member only
	 */
	RPCNode( char* uniqueID, void ( *_functionName ) ( char *input, int numberOfBitsOfData, PlayerID sender ) );
	/**
	 * Assignment operator
	 * @param input the node to copy
	 * @return a reference to the instance
	 */
	RPCNode& operator = ( const RPCNode& input );
	/**
	 * Copy constructor 
	 * @param input the node to copy 
	 */
	RPCNode( const RPCNode& input );
	/**
	 * Default constructor
	 */
	RPCNode();
	/**
	 * Destructor
	 */
	~RPCNode();
	/**
	 * Test if two RPCNode are equal.
	 * @param left An RPC node.
	 * @param right An RPC node.
	 * @return true if equal false otherwise.
	 */
	friend int operator==( const RPCNode& left, const RPCNode& right );
	/**
	 * Test if @em left is greater than @em right.
	 * @param left An RPC node.
	 * @param right An RPC node.
	 * @return true if @em left is greater than @em right.
	 */
	friend int operator > ( const RPCNode& left, const RPCNode& right );
	/**
	 * Test if @em left is lesser than @em right.
	 * @param left An RPC node.
	 * @param right An RPC node.
	 * @return true if @em left is lesser than @em right.
	 */
	friend int operator < ( const RPCNode& left, const RPCNode& right );
};

#endif

