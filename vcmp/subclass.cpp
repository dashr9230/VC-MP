
#include "main.h"

extern CGame			*pGame;

WNDPROC hOldProc;
LRESULT APIENTRY NewWndProc(HWND,UINT,WPARAM,LPARAM);

//----------------------------------------------------

BOOL HandleKeyPress(DWORD vKey)
{
	// TODO: HandleKeyPress
	return FALSE;
}

//----------------------------------------------------

BOOL HandleCharacterInput(DWORD dwChar)
{
	// TODO: HandleCharacterInput
	return FALSE;
}

//----------------------------------------------------

BOOL SubclassGameWindow()
{
	HWND hwndGameWnd = pGame->GetMainWindowHwnd();

	if(hwndGameWnd) {
		hOldProc = (WNDPROC)GetWindowLong(hwndGameWnd,GWL_WNDPROC);
		SetWindowLong(hwndGameWnd,GWL_WNDPROC,(LONG)NewWndProc);
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------

LRESULT APIENTRY NewWndProc( HWND hwnd,UINT uMsg,
							 WPARAM wParam,LPARAM lParam )
{
	switch(uMsg) {
		case WM_KEYUP:
			if(HandleKeyPress((DWORD)wParam)) { // 'I' handled it.
				return 0;
			}
			break;
		case WM_CHAR:
			if(HandleCharacterInput((DWORD)wParam)) { // 'I' handled it.
				return 0;
			}
			break;
	}
	return CallWindowProc(hOldProc,hwnd,uMsg,wParam,lParam);
}

//----------------------------------------------------
