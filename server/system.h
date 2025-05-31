
#pragma once

typedef struct _VECTOR {
	float X,Y,Z;
} VECTOR, *PVECTOR;

typedef struct _VECTOR_PAD {
	float X,Y,Z,pad;
} VECTOR_PAD, *PVECTOR_PAD;

typedef struct _MATRIX4X4 {
	VECTOR_PAD vLookRight;
	VECTOR_PAD vLookUp;
	VECTOR_PAD vLookAt;
	VECTOR_PAD vPos;
} MATRIX4X4, *PMATRIX4X4;

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
