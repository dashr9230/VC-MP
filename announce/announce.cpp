
#ifdef WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "httpclient.h"

#ifdef WIN32

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nShowCmd)
{
	CHttpClient* pHttpClient = new CHttpClient;

	OutputDebugString(lpszCmdLine);

	char szURL[255];
	sprintf(szURL, "66.55.69.94/masterlist.php?port=%s", lpszCmdLine);

	pHttpClient->ProcessURL(HTTP_GET, szURL, NULL, "NONREF");

	delete pHttpClient;

	ExitProcess(0);

	return 0;
}

#else

int main(int argc, char *argv[])
{
	CHttpClient* pHttpClient = new CHttpClient;

	char szURL[255];
	sprintf(szURL, "66.55.69.94/masterlist.php?port=%s", argv[1]);

	pHttpClient->ProcessURL(HTTP_GET, szURL, NULL, "NONREF");

	delete pHttpClient;

	return 0;
}

#endif
