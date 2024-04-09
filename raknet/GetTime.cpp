
#include "GetTime.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

unsigned int RakNet::GetTime( void )
{
#ifdef _WIN32
	static LARGE_INTEGER yo;
	static LONGLONG counts;
#else
	static timeval tp, initialTime;
#endif

	static bool initialized = false;

	if ( initialized == false )
	{
#ifdef _WIN32
		QueryPerformanceFrequency( &yo );
		// The original code shifted right 10 bits
		//counts = yo.QuadPart >> 10;
		// It gives the wrong value since 2^10 is not 1000
		counts = yo.QuadPart / 1000;
#else
		gettimeofday( &initialTime, 0 );
#endif

		initialized = true;
	}

#ifdef _WIN32
	LARGE_INTEGER PerfVal;

	QueryPerformanceCounter( &PerfVal );

	return ( unsigned int ) ( PerfVal.QuadPart / counts );
#else
	gettimeofday( &tp, 0 );

	// Seconds to ms and microseconds to ms
	return ( tp.tv_sec - initialTime.tv_sec ) * 1000 + ( tp.tv_usec - initialTime.tv_usec ) / 1000;
#endif
}
