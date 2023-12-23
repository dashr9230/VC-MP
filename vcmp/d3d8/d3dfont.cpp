
#include <tchar.h>
#include "include/D3DFont.h"

CD3DFont::CD3DFont( TCHAR* strFontName, DWORD dwHeight, DWORD dwFlags )
{
	_tcscpy( m_strFontName, strFontName );
	m_dwFontHeight         = dwHeight;
	m_dwFontFlags          = dwFlags;

	field_54 = 0;
	field_58 = 0;
	field_60 = 0;
	field_670 = 0;
	field_674 = 0;
	field_678 = 0;
}
