
#ifndef D3DFONT_H
#define D3DFONT_H
#include <tchar.h>
#include "d3d8.h"

class CD3DFont
{
	TCHAR   m_strFontName[80];            // Font properties
	DWORD   m_dwFontFlags;

	int field_54;
	int field_58;

	int field_60;

	int field_670;
	int field_674;
	int field_678;

public:
	DWORD   m_dwFontHeight;

	CD3DFont( TCHAR* strFontName, DWORD dwHeight, DWORD dwFlags=0L );
};

#endif


