
#ifndef _SYSTEM_H
#define _SYSTEM_H

typedef struct _VECTOR {
	float X,Y,Z;
} VECTOR, *PVECTOR;

#ifdef _WIN32
# include <windows.h>
#else

#ifndef FALSE
#define FALSE               0
#endif
#ifndef TRUE
#define TRUE                1
#endif

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;

#endif //!Win32

#endif // _SYSTEM_H
