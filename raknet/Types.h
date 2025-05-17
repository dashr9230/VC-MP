/* -*- mode: c++; c-file-style: raknet; tab-always-indent: nil; -*- */
/**
 * @file 
 * @brief Compatibility Layer and fundamental tools and types 
 * 
 * @verbatim
 * Fundamental tools & types
 *
 * Catid(cat02e@fsu.edu)
 *
 * 8/9/2004 Added SINGLE/ARRAY_RELEASE
 * 8/5/2004 Added COMPILER_ preprocessors
 *    class NoCopies
 * 8/1/2004 Removed mask stuff
 * 7/29/2004 Added swapLE, swapBE, getLE, getBE
 * 7/28/2004 Automatic and AutoArray now compile in dev-c++
 *    Added pre-processor conditions to support 
 *    other compilers
 *    Removed GETWORD and GETDWORD
 * 7/15/2004 Now using COM_RELEASE throughout CatGL3
 * 6/22/2004 Removed triple and pair
 * 6/12/2004 AutoDeallocate -> Automatic, AutoArray
 * 6/9/2004 OBJCLR
 * 5/2/2004 class AutoDeallocate
 * 5/1/2004 IS_POWER_OF_2, next_highest_power_of_2
 * 4/30/2004 Merged character manip macros
 * 2/23/2004 CEIL*
 *    Removed MEMCOPY32 and MEMCLEAR32,
 *    memcpy and memset are now faster
 *    MAKE_MASK
 * 2/10/2004 LITTLE_ENDIAN
 *    COUNT1BITS32
 *    AT_LEAST_2_BITS
 *    LEAST_SIGNIFICANT_BIT
 * X-mas/2003 [u/s]int?? -> [u/s]??
 * 7/3/2003 Added template triple, point->pair
 * 6/15/2003 Added template rect, point
 * 3/30/2003 Added RO?8, RO?16 and ?int64
 *    Added MEMCOPY32 and MEMCLEAR32
 * 3/12/2003 Added GETWORD and GETDWORD
 * 1/16/2003 Formalized this library.
 *
 * Tabs: 4 spaces
 * Dist: public
 * @endverbatim
 */

#ifndef TYPES_H
#define TYPES_H

// Rotation
#define ROL32(n, r) ( ((n) << (r)) | ((n) >> (32 - (r))) ) /* only works for u32 */

#endif // TYPES_H



