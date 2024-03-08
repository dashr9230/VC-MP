
#pragma once
#ifndef VCMPSRV_RCON_H
#define VCMPSRV_RCON_H

class CRcon
{
private:
	RakServerInterface* m_pRak;
public:
	CRcon(WORD iPort, char* szPass, WORD iMaxAdmins);

	void ConsoleOutput(char* szOutput);
	void ConsolePrintf( char* szFormat, ... );
};

#endif
