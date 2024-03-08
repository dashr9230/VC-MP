
#pragma once

typedef struct _VECTOR {
	float X,Y,Z;
} VECTOR, *PVECTOR;

//----------------------------------------------------

#ifdef _WIN32
# include <windows.h>
#else

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef char                CHAR;
typedef char				*PCHAR;

#endif //!Win32

//----------------------------------------------------
