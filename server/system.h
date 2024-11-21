
#ifndef _SYSTEM_H
#define _SYSTEM_H

typedef unsigned long       DWORD;

//----------------------------------------------------

#pragma pack(1)
typedef struct _VECTOR {
	float X,Y,Z;
} VECTOR, *PVECTOR;

#pragma pack(1)
typedef struct _MATRIX4X4 {
	VECTOR right;
	DWORD  flags;
	VECTOR up;
	float  pad_u;
	VECTOR at;
	float  pad_a;
	VECTOR pos;
	float  pad_p;
} MATRIX4X4, *PMATRIX4X4;

//----------------------------------------------------

#ifdef _WIN32
# include <windows.h>
#else
#ifndef FALSE
#define FALSE               0
#endif
#ifndef TRUE
#define TRUE                1
#endif

typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef char                CHAR;

#endif //!Win32

#endif // _SYSTEM_H
