/* -*- mode: c++; c-file-style: raknet; tab-always-indent: nil; -*- */
/**
 * @file
 * @brief NetworkObject Class Declaration 
 *
 * This file is part of RakNet Copyright 2003, 2004 Rakkarsoft LLC and
 * Kevin Jenkins.
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
#if !defined(AFX_NETWORKOBJECT_H__29266376_3F9E_42CD_B208_B58957E1935B__INCLUDED_)
#define      AFX_NETWORKOBJECT_H__29266376_3F9E_42CD_B208_B58957E1935B__INCLUDED_

#include "BinarySearchTree.h"
#include "NetworkTypes.h"

class NetworkObject;
/**
 * @brief  Define a node of an Object Tree. 
 * Used internally to contain objects in the tree.  Ignore this
 */

struct ObjectIDNode
{
	/**
	 * id 
	 */
	unsigned short objectID;
	/**
	 * a pointer to the object associated to id 
	 */
	NetworkObject *object;
	/**
	 * Default Constructor
	 */
	ObjectIDNode();
	/**
	 * Create a node based on the objectID and a pointer to the NetworkObject 
	 * @param ObjectID id of the node
	 * @param Object the network object 
	 */
	ObjectIDNode( unsigned short ObjectID, NetworkObject *Object );
	/**
	 * Test if two nodes are equals 
	 * @param left a node
	 * @param right a node 
	 * @return true if the nodes are the same 
	 */
	friend int operator==( const ObjectIDNode& left, const ObjectIDNode& right );
	/**
	 * Test if one node is greater than the other 
	 * @param left a node
	 * @param right a node
	 * @return True if @em left is greater than @em right 
	 */
	friend int operator > ( const ObjectIDNode& left, const ObjectIDNode& right );
	/**
	 * Test if one node is lesser than the other 
	 * @param left a node
	 * @param right a node
	 * @return True if @em left is lesser than @em right 
	 */
	friend int operator < ( const ObjectIDNode& left, const ObjectIDNode& right );
};

/**
 * A NetworkObject is used to identify uniquely an object on the
 * network You can easly create object with network unique id by
 * subclassing this class.
 */

class NetworkObject
{

public:
	/**
	 * Default Constructor
	 */
	NetworkObject();
	/**
	 * Default Destructor
	 */
	virtual ~NetworkObject();
	/**
	 * Get the id of the object 
	 * @return the id of the current object 
	 */
	virtual unsigned short GetID( void ) const;
	/**
	 * Associate an id to an object 
	 * @param id the new id of the network object.
	 * @note Only the server code should
	 * call this.
	 *
	 */
	virtual void SetID( unsigned short id );
	/**
	 * Store all object in an AVL using id as key 
	 */
	static BasicDataStructures::AVLBalancedBinarySearchTree<ObjectIDNode> IDTree;
	/**
	 * These function is only meant to be used when saving games as you
	 * should save the HIGHEST value staticItemID has achieved upon save
	 * and reload it upon load.  Save AFTER you've created all the items
	 * derived from this class you are going to create.  
	 * @return the HIGHEST Object Id currently used 
	 */
	static unsigned short GetStaticItemID( void );
	/**
	 * These function is only meant to be used when loading games. Load
	 * BEFORE you create any new objects that are not SetIDed based on
	 * the save data. 
	 * @param i the highest number of NetworkObject reached. 
	 */
	static void SetStaticItemID( unsigned short i );
	
protected:
	/**
	 * The  network ID of this object
	 */
	unsigned short objectID;
	/**
	 * Store whether or not its a server assigned ID 
	 */
	bool serverAssignedID;
	
private:
	/**
	 * Number of network object. 
	 */
	static unsigned short staticItemID;
};

/**
 * Retrieve a NetworkObject from its ID 
 * @param x the object id 
 * @return a pointer to a NetworkObject or 0 if there is no corresponding Id. 
 */
NetworkObject* GET_OBJECT_FROM_ID( ObjectID x );

#endif // !defined(AFX_NETWORKOBJECT_H__29266376_3F9E_42CD_B208_B58957E1935B__INCLUDED_)
