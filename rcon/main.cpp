
#include "main.h"

void logprintf(char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	char buffer[512];
	vsprintf(buffer, format, ap);
	va_end(ap);
	puts(buffer);
}

CRconClient* pRconClient = NULL;
bool bQuitApp = false;

BOOL WINAPI CtrlHandler(DWORD dwType)
{
	switch (dwType)
	{
		case CTRL_C_EVENT:
		case CTRL_BREAK_EVENT:
		case CTRL_CLOSE_EVENT:
		case CTRL_LOGOFF_EVENT:
		case CTRL_SHUTDOWN_EVENT:
			bQuitApp = true;
			return TRUE;
	}
	return FALSE;
}

HANDLE hConsoleExecuteEvent;

DWORD WINAPI ConsoleInputThread(void* pParam)
{
	char buf[512];
	while (true)
	{
		DWORD dwRead;
		ReadConsole(GetStdHandle(STD_INPUT_HANDLE), buf, 255, &dwRead, NULL);
		if (dwRead > 2)
		{
			buf[dwRead-2] = 0;
			WaitForSingleObject(hConsoleExecuteEvent, INFINITE);
			pRconClient->Command(buf);
			SetEvent(hConsoleExecuteEvent);
		}
	}
}

int main (int argc, char** argv)
{
	char szServerIp[32];
	char szPort[32];
	char szPassword[32];

	// Print welcome message.
	puts("\n VC:MP Command Line Remote Console Client");
	puts(" ----------------------------------------");
	puts(" v1.2, 4th Jul 2007\n");

	// If there's not enough command line args, print usage.
	if (argc < 3)
	{
		printf("Enter Server IP: ");
		scanf("%s", szServerIp);
		argv[1] = szServerIp;
		printf("IP: %s\n\n", szServerIp);

		printf("Enter Server RCON Port: ");
		scanf("%s", szPort);
		argv[2] = szPort;
		printf("Port: %s\n\n", szPort);

		printf("Enter Server RCON Password: ");
		scanf("%s", szPassword);
		argv[3] = szPassword;
		printf("Password: %s\n\n", szPassword);
	}

	// Setup the console
	SetConsoleCtrlHandler(CtrlHandler, TRUE);
	hConsoleExecuteEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	DWORD dwThreadId;
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ConsoleInputThread, NULL, 0, &dwThreadId);

	// Setup the Remote Console client.
	pRconClient = new CRconClient(argv[1], atoi(argv[2]), argv[3]);

	// While not wanting to quit...
	while (!bQuitApp)
	{
		// Process Remote Console client network messages.
		pRconClient->Process();
		// Get input.
		SetEvent(hConsoleExecuteEvent);
		WaitForSingleObject(hConsoleExecuteEvent, INFINITE);
		// Sleep for 100ms
		Sleep(100);
	}

	// Delete the Remote Console client.
	delete pRconClient;

	// Kill the input thread.
	TerminateThread(hThread, 0);
	CloseHandle(hConsoleExecuteEvent);

	return 0;
}
