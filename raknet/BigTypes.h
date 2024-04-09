
#ifndef BIGTYPES_H
#define BIGTYPES_H

#include "Types.h"

namespace big
{

	typedef u32 word; // assembly implementation is for 32-bit word size

	// template operator parameter modes
#define BIGONETYPE template<class T> /* supports only one class */

#define BIGWORDCOUNT_FROMBITCOUNT(bits) ((bits) / 8 / sizeof(big::word))

	typedef word u256[ BIGWORDCOUNT_FROMBITCOUNT( 256 ) ];

}

#endif // BIGTYPES_H

