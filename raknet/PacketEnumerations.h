// This file is part of RakNet Copyright 2003, 2004 Rakkarsoft LLC and Kevin Jenkins.

// Usage of Raknet is subject to the appropriate licence agreement.
// "Shareware" Licensees with Rakkarsoft LLC are subject to the shareware license found at http://www.rakkarsoft.com/shareWareLicense.html which you agreed to upon purchase of a "Shareware license"
// "Commercial" Licensees with Rakkarsoft LLC are subject to the commercial license found at http://www.rakkarsoft.com/sourceCodeLicense.html which you agreed to upon purchase of a "Commercial license"
// All other users are subject to the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

// Refer to the appropriate license agreement for distribution, modification, and warranty rights.

#ifndef __PACKET_ENUMERATIONS_H
#define __PACKET_ENUMERATIONS_H

enum {

	//
	// YOUR TYPES HERE!
	// WARNING - By default it is assumed that the packet identifier is one byte (unsigned char)
	// In the unlikely event that you need more than 256 types, including the built-in types, then you'll need
	// to request a special edition with larger identifiers, or change it yourself
	//

	ID_RCON_RESPONSE = 53,
};

#endif
